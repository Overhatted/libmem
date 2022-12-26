#include "internal.h"

LM_API lm_bool_t
LM_Assemble(lm_cstring_t code,
	    lm_inst_t   *inst)
{
	lm_bool_t  ret = LM_FALSE;
	lm_byte_t *codebuf;

	if (!LM_AssembleEx(code, LM_ARCH, LM_BITS, (lm_address_t)0, &codebuf))
		return LM_FALSE;

	LM_Disassemble(codebuf, inst);

	LM_FreeCodeBuffer(&codebuf);

	return LM_TRUE;
}

/********************************/

LM_API lm_size_t
LM_AssembleEx(lm_cstring_t code,
	      lm_arch_t    arch,
	      lm_size_t    bits,
	      lm_address_t base_addr,
	      lm_byte_t  **pcodebuf)
{
	lm_size_t      ret = 0;
	ks_engine     *ks;
	ks_arch        ksarch;
	ks_mode        ksmode;
	unsigned char *encode;
	size_t         size;
	size_t         count;
	lm_byte_t     *codebuf;

	LM_ASSERT(code != LM_NULLPTR && pcodebuf != LM_NULLPTR);

	switch (arch) {
	case LM_ARCH_X86: ksarch = KS_ARCH_X86; break;
	case LM_ARCH_ARM: ksarch = KS_ARCH_ARM; break;
	default: return ret;
	}

	switch (bits) {
	case 32: ksmode = KS_MODE_32; break;
	case 64: ksmode = KS_MODE_64; break;
	default: return ret;
	}

	if (ks_open(ksarch, ksmode, &ks) != KS_ERR_OK)
		return ret;

	ks_asm(ks, code, 0, &encode, &size, &count);

	codebuf = (lm_byte_t *)LM_MALLOC(size);
	if (!codebuf)
		goto FREE_RET;

	LM_MEMCPY((void *)codebuf, encode, size);

	*pcodebuf = codebuf;
	ret = (lm_size_t)size;
FREE_RET:
	ks_free(encode);
CLEAN_EXIT:
	ks_close(ks);
	return ret;
}

/********************************/

LM_API lm_void_t
LM_FreeCodeBuffer(lm_byte_t **pcodebuf)
{
	if (*pcodebuf)
		LM_FREE(*pcodebuf);
	*pcodebuf = (lm_byte_t *)LM_NULLPTR;
}

/********************************/

LM_API lm_bool_t
LM_Disassemble(lm_address_t code, lm_inst_t *inst)
{
	lm_bool_t ret = LM_FALSE;
	lm_inst_t *insts;

	LM_ASSERT(code != LM_ADDRESS_BAD && inst != LM_NULLPTR);

	if (!LM_DisassembleEx(code, LM_ARCH, LM_BITS,
			      LM_INST_SIZE, 1, (lm_address_t)0, &insts))
		return LM_FALSE;

	*inst = *insts;

	LM_FreeInstructions(&insts);

	return LM_TRUE;
}

/********************************/

LM_API lm_size_t
LM_DisassembleEx(lm_address_t code,
		 lm_arch_t    arch,
		 lm_size_t    bits,
		 lm_size_t    size,
		 lm_size_t    count,
		 lm_address_t base_addr,
		 lm_inst_t  **pinsts)
{
	lm_size_t ret = 0;
	csh cshandle;
	cs_insn *csinsn;
	cs_arch csarch;
	cs_mode csmode;
	size_t inst_count;
	lm_inst_t *insts = (lm_inst_t *)LM_NULLPTR;
	size_t i;

	LM_ASSERT(code != LM_ADDRESS_BAD && pinsts != LM_NULLPTR);

	switch (arch) {
	case LM_ARCH_X86: csarch = CS_ARCH_X86; break;
	case LM_ARCH_ARM: csarch = CS_ARCH_ARM; break;
	default: return ret;
	}

	switch (bits) {
	case 32: csmode = CS_MODE_32; break;
	case 64: csmode = CS_MODE_64; break;
	default: return ret;
	}

	if (cs_open(csarch, csmode, &cshandle) != CS_ERR_OK)
		return ret;

	inst_count = cs_disasm(cshandle, code, size, base_addr, count, &csinsn);
	if (inst_count <= 0)
		goto CLEAN_EXIT;

	insts = LM_CALLOC(inst_count, sizeof(lm_inst_t));
	if (!insts)
		goto FREE_EXIT;

	for (i = 0; i < inst_count; ++i) {
		LM_MEMCPY((void *)&insts[i], (void *)&csinsn[i],
			  sizeof(lm_inst_t));
	}

	*pinsts = insts;
	ret = (lm_size_t)inst_count;
FREE_EXIT:
	cs_free(csinsn, inst_count);
CLEAN_EXIT:
	cs_close(&cshandle);
	return ret;
}

/********************************/

LM_API lm_void_t
LM_FreeInstructions(lm_inst_t **pinsts)
{
	if (*pinsts)
		LM_FREE(*pinsts);

	*pinsts = (lm_inst_t *)LM_NULLPTR;
}

/********************************/

LM_API lm_size_t
LM_CodeLength(lm_address_t code, lm_size_t minlength)
{
	lm_size_t length;
	lm_inst_t inst;

	LM_ASSERT(code != LM_ADDRESS_BAD && minlength > 0);

	for (length = 0; length < minlength; code = (lm_address_t)LM_OFFSET(code, length)) {
		if (LM_Disassemble(code, &inst) == LM_FALSE)
			return 0;
		length += inst.size;
	}

	return length;
}

/********************************/

LM_API lm_size_t
LM_CodeLengthEx(lm_process_t proc,
		lm_address_t code,
		lm_size_t minlength)
{
	lm_size_t length;
	lm_inst_t inst;
	lm_byte_t codebuf[LM_INST_SIZE];

	LM_ASSERT(LM_VALID_PROCESS(proc) &&
		  code != LM_ADDRESS_BAD &&
		  minlength > 0);

	for (length = 0; length < minlength; code = (lm_address_t)LM_OFFSET(code, length)) {
		LM_ReadMemoryEx(proc, code, codebuf, sizeof(codebuf));
		if (LM_Disassemble(codebuf, &inst) == LM_FALSE)
			return 0;
		length += inst.size;
	}

	return length;
}
