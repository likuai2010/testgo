package main

/*
#cgo LDFLAGS: -lhilog_ndk.z
*/
import "C"


//export coreTest
func coreTest() C.int {
	return 1
}



func main() {
	panic("Stub!")
}