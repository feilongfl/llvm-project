#CC-RH Compiler RH850 Assembler Source
#@	CC-RH Version : V2.03.00 [26 Nov 2020]
#@	Command : main.c -oDefaultBuild\main.obj -Xcpu=g3kh -g -g_line -Onothing -Xdbl_size=4 -Xasm_path=DefaultBuild -c
#@	compiled at Mon Jul 19 06:09:12 2021

	.file "main.c"

	$reg_mode 32

	.public _test
	.public _main

	.section .text, text
_test:
	.stack _test = 4
	.line "C:/Users/feilong/Documents/test/main.c", 32
	add 0xFFFFFFFC, r3
	.line "C:/Users/feilong/Documents/test/main.c", 33
	st.w r0, 0x00000000[r3]
	mov 0x00000000, r10
.BB.LABEL.1_1:	; entry.split
	.line "C:/Users/feilong/Documents/test/main.c", 34
	dispose 0x00000004, 0x00000000, [r31]
_main:
	.stack _main = 8
	.line "C:/Users/feilong/Documents/test/main.c", 36
	prepare 0x00000001, 0x00000004
	.line "C:/Users/feilong/Documents/test/main.c", 38
	jarl _test, r31
.BB.LABEL.2_1:	; entry.split
	.line "C:/Users/feilong/Documents/test/main.c", 39
	st.w r0, 0x00000000[r3]
	mov 0x00000000, r10
.BB.LABEL.2_2:	; entry.split1
	.line "C:/Users/feilong/Documents/test/main.c", 40
	dispose 0x00000004, 0x00000001, [r31]
