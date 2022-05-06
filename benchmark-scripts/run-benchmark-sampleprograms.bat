if "%1"=="" ( 
    echo "Analyzer.exe should be provided as argument"
    exit
)

for /l %%i in (1, 1, 10) do (
    %~f1 -ba .\sampleprograms\medium-size-program.sc
)

for /l %%i in (1, 1, 10) do (
    %~f1 -ba .\sampleprograms\small-array-sample.sc
)

for /l %%i in (1, 1, 10) do (
    %~f1 -ba .\sampleprograms\taint-into-param-test.sc
)