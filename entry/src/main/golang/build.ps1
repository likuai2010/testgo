$arch="arm64"
# amd64  arm64
$target="aarch64"
# x86_64 aarch64
$outdir="arm64-v8a"
# x86_64 arm64-v8a
$OHOS_NATIVE_HOME="G:/huawei/DevEcoStudio/sdk/default/openharmony/native"
$BASE_FLAGS="-Wno-error --sysroot=$OHOS_NATIVE_HOME/sysroot -fdata-sections -D__MUSL__ -ffunction-sections -funwind-tables -fstack-protector-strong -no-canonical-prefixes -fno-addrsig -Wa,--noexecstack -fPIC"
$TOOLCHAIN="$OHOS_NATIVE_HOME/llvm"

$env:CC = "$TOOLCHAIN/bin/clang "
$env:CXX= "$TOOLCHAIN/bin/clang++"
$env:LD = "$TOOLCHAIN/bin/clang"
$env:CGO_AR= "$TOOLCHAIN/bin/llvm-ar"
$CGO_AR= "$TOOLCHAIN/bin/llvm-ar"
$env:GOASM= "$TOOLCHAIN/bin/llvm-as"

$env:GOOS = "linux"
$env:GOARCH = $arch # amd64 386 arm arm64
$env:GOARM = "";
$env:CGO_ENABLED = "1"
$env:CGO_CXXFLAGS=""
$env:CGO_CFLAGS = "-Wno-error --target=$target-linux-ohos  $BASE_FLAGS  "
$env:CGO_LDFLAGS = "-extld=$env:LD --sysroot=$OHOS_NATIVE_HOME/sysroot --target=$target-linux-ohos"

$sourceFile = "./native"
$outputFile = "gotest.so"
# 压缩so
# -trimpath -ldflags="-s -w"
G:\git\golang_go\bin\go build -tlsmodegd -buildmode c-shared   -v -o $outputFile $sourceFile

# 检查编译结果
if (Test-Path $outputFile) {
    Write-Host "success: $outputFile"
} else {
    Write-Host "failed"
}
Copy-Item -Force "$PSScriptRoot\gotest.so" "$PSScriptRoot\..\..\..\libs\$outdir\gotest.so"
#Copy-Item -Force "$PSScriptRoot\dist\index.d.ts" "$PSScriptRoot\..\src\main\cpp\types\hello\index.d.ts"