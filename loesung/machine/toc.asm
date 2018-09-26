; $Id: toc.asm 956 2008-10-19 22:24:23Z hsc $

;******************************************************************************
;* Betriebssysteme                                                            *
;*----------------------------------------------------------------------------*
;*                                                                            *
;*                               T O C . A S M                                *
;*                                                                            *
;*----------------------------------------------------------------------------*
;*
;******************************************************************************

%include "machine/toc.inc"

; EXPORTIERTE FUNKTIONEN

[GLOBAL toc_switch]
[GLOBAL toc_go]

; IMPLEMENTIERUNG DER FUNKTIONEN

 ;ebx_offset:	resd 1
;esi_offset:	resd 1
;edi_offset:	resd 1
;ebp_offset:	resd 1
;esp_offset:	resd 1

[SECTION .text]

; TOC_GO : Startet den ersten Prozess ueberhaupt.
;
; C Prototyp: void toc_go (struct toc* regs);

toc_go:
	push ebp
	mov ebp, esp
	mov eax, [ebp + 8] ; regs pointer
	mov ebx, [eax + ebx_offset]
	mov esi, [eax + esi_offset]
	mov edi, [eax + edi_offset]
	mov esp, [eax + esp_offset]
	mov ebp, [eax + ebp_offset]
	ret



; Hier muesst ihr selbst Code vervollstaendigen         

; TOC_SWITCH : Prozessumschaltung. Der aktuelle Registersatz wird     
;              gesichert und der Registersatz des neuen "thread of control"
;              wird in den Prozessor eingelesen.  
;
; C Prototyp: void toc_switch (struct toc* regs_now,
;                              struct toc* reg_then);

toc_switch:
	
	mov eax, [esp + 4] ; regs_now pointer
	mov ecx, [esp + 8] ; reg_then pointer
	
	mov [eax + ebx_offset], ebx
	mov [eax + esi_offset], esi
	mov [eax + edi_offset], edi
	mov [eax + esp_offset], esp
	mov [eax + ebp_offset], ebp
	
	mov ebx, [ecx + ebx_offset]
	mov esi, [ecx + esi_offset]
	mov edi, [ecx + edi_offset]
	mov esp, [ecx + esp_offset]
	mov ebp, [ecx + ebp_offset]
	
	ret

; Hier muesst ihr selbst Code vervollstaendigen 
