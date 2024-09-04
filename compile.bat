cd %~dp0
chcp 65001
C:\msys64\usr\bin\bash --login -c "DIR=%cd:\=\\\\%; cd $(cygpath $DIR) && ./compile.sh"

copy _build32\io42wajv\io42wajv.dll W:\apm\BB10\App\app\wajvio.dll