if "%1"=="" ( 
    echo "Analyzer.exe should be provided as argument"
    exit
)

for /l %%i in (1, 1, 10) do (
    %~f1 -ba -d f 1 .\sampleprograms\low-parallel.sc
)

for /l %%i in (1, 1, 10) do (
    %~f1 -ba -d f 5 .\sampleprograms\low-parallel.sc
)

for /l %%j in (10, 10, 100) do (
    for /l %%i in (1, 1, 10) do (
         %~f1 -ba -d f %%j .\sampleprograms\low-parallel.sc
    )
)

for /l %%j in (150, 50, 500) do (
    for /l %%i in (1, 1, 10) do (
         %~f1 -ba -d f %%j .\sampleprograms\low-parallel.sc
    )
)

for /l %%j in (600, 100, 1500) do (
    for /l %%i in (1, 1, 10) do (
         %~f1 -ba -d f %%j .\sampleprograms\low-parallel.sc
    )
)

for /l %%j in (2000, 1000, 10000) do (
    for /l %%i in (1, 1, 10) do (
         %~f1 -ba -d f %%j .\sampleprograms\low-parallel.sc
    )
)