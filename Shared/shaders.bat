@echo off
setlocal enabledelayedexpansion


set SLANGC="%VULKAN_SDK%\Bin\slangc.exe"
set SHADER_DIR=..\Game\resources\shaders

echo -- [shaders] Compilando shaders .slang en %SHADER_DIR%
for %%f in (%SHADER_DIR%\*.slang) do (
    set "SOURCE=%%~f"
    set "OUTPUT=%%~f.spv"
    echo -- [shaders] Fuente: !SOURCE!
    echo -- [shaders] Salida: !OUTPUT!
    %SLANGC% !SOURCE! -target spirv -profile spirv_1_4 -emit-spirv-directly -fvk-use-entrypoint-name -entry vertMain -entry fragMain -o !OUTPUT!
)
echo -- [shaders] Shaders .slang compilados correctamente.