.586P
.MODEL FLAT, STDCALL
includelib kernel32.lib

ExitProcess PROTO: DWORD

.STACK 4096

.CONST 
Arr sdword 12, 14, -12, 7, 13, 18, 1, 8, -24, 69

.DATA
min sdword ?
max sdword ?

.CODE

main PROC
START:

push lengthof Arr
push offset Arr
call getmin
mov min, eax

push lengthof Arr
push offset Arr
call getmax
mov max, eax

push 0
call ExitProcess
main ENDP


getmin PROC uses ecx esi ebx, parr: dword, elem: dword

      mov   ecx, elem
      mov   esi, parr
      mov   ebx, [esi]
CYCLE: 
      lodsd
      cmp   eax, ebx
      jge   FALSE
      xchg  ebx, eax 
FALSE: 
      loop  CYCLE
      xchg eax, ebx
	ret
getmin ENDP


getmax PROC uses ecx esi ebx, parr: dword, elem: dword

      mov   ecx, elem
      mov   esi, parr
      mov   ebx, [esi]
CYCLE: 
      lodsd
      cmp   eax, ebx
      jle   FALSE
      xchg  ebx, eax 
FALSE: 
      loop  CYCLE
      xchg ebx, eax
	ret
getmax ENDP

END main