;*****************************************************************************
;*                                                                           *
;*                            C O R O U T I N E                              *
;*                                                                           *
;*---------------------------------------------------------------------------*
;* Beschreibung:    Assemblerdarstellung der 'struct CoroutineState' aus     *
;*                  CoroutineState.h                                         *
;*                                                                           *
;*                  Die Reihenfolge der Registerbezeichnungen muss unbedingt *
;*                  mit der von 'struct CoroutineState' uebereinstimmen.     *
;*                                                                           *
;* Autor:           Olaf Spinczyk, TU Dortmund                               *
;*****************************************************************************

%include "kernel/threads/Thread.inc"

; EXPORTIERTE FUNKTIONEN

[GLOBAL Thread_switch]
[GLOBAL Thread_start]

; IMPLEMENTIERUNG DER FUNKTIONEN

[SECTION .text]

; THREAD_START : Startet den ersten Thrad ueberhaupt.
;
; C Prototyp: void Thread_start (struct ThreadState* regs);

Thread_start:


	mov eax, [esp+4]	;regs

;	Den State von regs uebertragen
	mov esp, [eax+esp_offset]
	mov ebx, [eax+ebx_offset]
	mov esi, [eax+esi_offset]
	mov edi, [eax+edi_offset]
	mov ebp, [eax+ebp_offset]

	ret


; THREAD_SWITCH : Coroutinenumschaltung. Der aktuelle Registersatz wird
;                    gesichert und der Registersatz der neuen Coroutine
;                    wird in den Prozessor eingelesen.
;
; C Prototyp: void thread_switch (struct CoroutineState* regs_now,
;                                    struct CoroutineState* reg_then);
;
; Achtung: Die Parameter werden von rechts nach links uebergeben.
;
Thread_switch:

	mov eax, [esp+4]	;regs_now
	mov ecx, [esp+8]	;reg_then

;	Sichern des State in regs_now
	mov [eax + ebx_offset], ebx
	mov [eax + esi_offset], esi
	mov [eax + edi_offset], edi
	mov [eax + ebp_offset], ebp
	mov [eax + esp_offset], esp
	mov [eax + eax_offset], eax
	mov [eax + ecx_offset], ecx
	mov [eax + edx_offset], edx
; Sichern der flags
;	pushf
;	pop ecx
;	mov [eax + efl_offset], ecx


;	Den State von reg_then uebertragen
; Flags uebertragen
;	mov eax, [ecx + efl_offset]
;	push eax
;	popf

	mov ebx, [ecx + ebx_offset]
	mov esi, [ecx + esi_offset]
	mov edi, [ecx + edi_offset]
	mov ebp, [ecx + ebp_offset]
	mov esp, [ecx + esp_offset]
	mov eax, [ecx + eax_offset]
	mov edx, [ecx + edx_offset]
	mov ecx, [ecx + ecx_offset]
	

	ret
