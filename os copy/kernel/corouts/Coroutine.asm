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

%include "kernel/corouts/Coroutine.inc"

; EXPORTIERTE FUNKTIONEN

[GLOBAL Coroutine_switch]
[GLOBAL Coroutine_start]

; IMPLEMENTIERUNG DER FUNKTIONEN

[SECTION .text]

; COROUTINE_START : Startet die erste Coroutine ueberhaupt.
;
; C Prototyp: void Coroutine_start (struct CoroutineState* regs);

Coroutine_start:


	mov eax, [esp+4]	;regs

;	Den State von regs uebertragen
	mov esp, [eax+esp_offset]
	mov ebx, [eax+ebx_offset]
	mov esi, [eax+esi_offset]
	mov edi, [eax+edi_offset]
	mov ebp, [eax+ebp_offset]

	ret


; COROUTINE_SWITCH : Coroutinenumschaltung. Der aktuelle Registersatz wird
;                    gesichert und der Registersatz der neuen Coroutine
;                    wird in den Prozessor eingelesen.
;
; C Prototyp: void Coroutine_switch (struct CoroutineState* regs_now,
;                                    struct CoroutineState* reg_then);
;
; Achtung: Die Parameter werden von rechts nach links uebergeben.
;
Coroutine_switch:

	mov eax, [esp+4]	;regs_now
	mov ecx, [esp+8]	;reg_then

;	Sichern des State in regs_now
	mov [eax + ebx_offset], ebx
	mov [eax + esi_offset], esi
	mov [eax + edi_offset], edi
	mov [eax + ebp_offset], ebp
	mov [eax + esp_offset], esp


;	Den State von reg_then uebertragen
	mov ebx, [ecx + ebx_offset]
	mov esi, [ecx + esi_offset]
	mov edi, [ecx + edi_offset]
	mov ebp, [ecx + ebp_offset]
	mov esp, [ecx + esp_offset]

	ret
