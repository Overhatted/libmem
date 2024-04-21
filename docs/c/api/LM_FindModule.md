# LM_FindModule

```c
LM_API lm_bool_t LM_CALL
LM_FindModule(lm_string_t  name,
	      lm_module_t *module_out);
```

# Description
The function `LM_FindModule` searches for a module by name and populates the `module_out` parameter with
the found module information.

# Parameters
 - `name`: The `name` parameter is a string representing the name of the module that you are trying
to find (e.g `game.dll`). It can also be a relative path, such as `/game/hello` for a module at `/usr/share/game/hello`.
 - `module_out`: The `module_out` parameter is a pointer to a `lm_module_t` structure. This function
populates this structure with information about the found module, containing information such as base,
end, size, path and name.

# Return Value
The function `LM_FindModule` returns `LM_TRUE` if the module is found successfully,
otherwise it returns `LM_FALSE`.