import os
import subprocess
import sys

VCPKG_REPO = "https://github.com/microsoft/vcpkg.git"
SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
VCPKG_DIR = os.path.abspath(os.path.join(SCRIPT_DIR, "../External/Source/vcpkg"))
VCPKG_JSON = os.path.abspath(os.path.join(SCRIPT_DIR, "vcpkg.json"))
VCPKG_INSTALLED = os.path.abspath(os.path.join(SCRIPT_DIR, "../External/Source/vcpkg_installed"))

def run(cmd, cwd=None):
    print(f"Ejecutando: {cmd}")
    result = subprocess.run(cmd, shell=True, cwd=cwd)
    if result.returncode != 0:
        print("Error ejecutando el comando.")
        sys.exit(result.returncode)

def main():
    # 1. Clonar vcpkg si no existe
    if not os.path.isdir(VCPKG_DIR):
        run(f"git clone --depth 1 {VCPKG_REPO} \"{VCPKG_DIR}\"")
    else:
        print("vcpkg ya está clonado.")

    # 2. Bootstrap vcpkg
    if os.name == "nt":
        bootstrap_cmd = ".\\bootstrap-vcpkg.bat"
        vcpkg_exe = os.path.join(VCPKG_DIR, "vcpkg.exe")
    else:
        bootstrap_cmd = "./bootstrap-vcpkg.sh"
        vcpkg_exe = os.path.join(VCPKG_DIR, "vcpkg")
    run(bootstrap_cmd, cwd=VCPKG_DIR)

    # 3. Instalar dependencias desde vcpkg.json si existe
    if os.path.isfile(VCPKG_JSON):
        run(f"\"{vcpkg_exe}\" install --x-install-root=\"{VCPKG_INSTALLED}\"", cwd=SCRIPT_DIR)
    else:
        print("No se encontró vcpkg.json en Scripts/. Crea uno ahí para instalar dependencias automáticamente.")

    print("¡Listo! Ahora puedes configurar tu proyecto con CMake y vcpkg.")

if __name__ == "__main__":
    main()