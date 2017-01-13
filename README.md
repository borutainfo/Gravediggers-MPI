#Gravediggers-MPI

## Konfiguracja

#### Windows 7
Trzeba zainstalować następujące aplikacje / biblioteki:
1. MinGW a w nim dodatkowe pakiety (nie wiem czy to wszystkie wymagane:)
    - mingw32-gcc
    - mingw32-gcc-g++
    - mingw32-make
2. CMake (min. 3.6)
3. Microsoft .NET Framework Version 1.1 Redistributable Package
4. mpich2-1.2.1-win-ia32

W pliku CMakeLists.txt należy ustawić właściwe ścieżki do plików / katalogów.
 
Jeśli wystąpią problemy z linkerem należy upewnić się że wersja biblioteki MPICH jest przeznaczona dla architektury 32 bitowej.

Do uruchomienia na Windowsie w moim przypadku musiałem jeszcze przekopiować DLL'ki do folderu z mpiexec (libgcc_s_dw2-1.dll, libstdc++-6.dll). Warto dodać katalog z mpiexec do zmiennej środowiskowej PATH.


