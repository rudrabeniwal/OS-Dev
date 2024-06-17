[BITS 16]
[ORG 0x7c00]

start:
    xor ax,ax   
    mov ds,ax
    mov es,ax  
    mov ss,ax
    mov sp,0x7c00

TestDiskExtension:
    mov [DriveId], dl   ; Save drive ID (passed by BIOS in DL) to variable
    mov ah, 0x41        ; Function 0x41 - Check for Extensions Supported
    mov bx, 0x55aa      ; Magic number required by the BIOS for the function
    int 0x13            ; BIOS disk services
    jc NotSupport       ; If carry flag is set, extensions are not supported
    cmp bx, 0xaa55      ; Check if BIOS returned the magic number
    jne NotSupport      ; If not, extensions are not supported
LoadLoader:
    mov si, ReadPacket
    mov word[si], 0x10 ; The first two bytes of the packet are set to 0x10, indicating the size of the packet (16 bytes)
    mov word[si+2], 5 ;The next two bytes specify the number of sectors to read (5 sectors)
    mov word[si+4], 0x7e00  ; Buffer address (segment:offset -> 0000:7e00)
    mov word[si+6], 0       ; Buffer segment (0 in this case, using real mode segment:offset addressing)
    mov dword[si+8], 1      ; Starting LBA (Logical Block Address) of the read
    mov dword[si+0xc], 0    ; Reserved, should be zero
    mov dl, [DriveId]
    mov ah, 0x42
    int 0x13
    jc ReadError

    mov dl, [DriveId]
    jmp 0x7e00
ReadError:
NotSupport:
    mov ah,0x13
    mov al,1
    mov bx,0xa
    xor dx,dx
    mov bp,Message
    mov cx,MessageLen 
    int 0x10

End:
    hlt    
    jmp End

DriveId: db 0
     
Message:    db "We have error in boot process"
MessageLen: equ $-Message
ReadPacket: times 16 db 0

times (0x1be-($-$$)) db 0

    db 80h
    db 0,2,0
    db 0f0h
    db 0ffh,0ffh,0ffh
    dd 1
    dd (20*16*63-1)
	
    times (16*3) db 0

    db 0x55
    db 0xaa

	
