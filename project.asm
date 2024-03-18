section .text

global f1
f1:
    push ebp
    mov ebp, esp
    finit
    fld dword[ebp+8]
    fchs ;st[0] -> (-x)
    fldl2e ;st[0] -> log2e, st[1] -> (-x)
    fmulp ;st[0] = (-x)*log2e
    sub esp, 8
    fstp dword[esp]
    fld dword[esp] ;(-x)*log2e
    fld dword[esp] ;(-x)*log2e
    FRNDINT
    fst dword[esp+4] ;округленное число
    FSUBP
    fstp dword[esp] ;наше число
    ;for okr
    fld dword[esp+4];st[1] = x
    FLD1 ;st[0]=1
    fscale ;st[0]=1*2^x
    
    fstp dword[esp+4]; okr = 1*2^x
    mov eax, dword[esp+4]
    fld dword[esp];x
    F2XM1;st[0]=2^st[0]-1=2^x-1
    FLD1
    faddp ;drob'
    fst dword[esp] ;s[0] drob'
    mov eax, dword[esp]
    fld dword[esp+4]
    fmulp
    mov dword[esp], 1077936128
    fld dword[esp]
    faddp
    add esp, 8
    
    mov esp, ebp
    pop ebp
    ret
    
global f2   
f2:
    push ebp
    mov ebp, esp
    finit
    fld dword[ebp+8]
    sub esp, 8
    mov dword[esp], 1073741824 
    fld dword[esp]
    fmulp ;st[0] = 2x
    sub esp, 8
    fstp dword[esp]
    fld dword[esp] ;st[1] = 2x
    fld dword[esp] ;st[0] = 2x
    
    mov dword[esp], 1073741824
    fld dword[esp]
    fsubp
    add esp, 8
   
    mov esp, ebp
    pop ebp
    ret

global f3
f3:
    push ebp
    mov ebp, esp
    finit
    sub esp, 8
    mov dword[esp], 1065353216 ;(1)
    fld dword[esp] ;st[1] = 1
    fld dword[ebp+8] ;st[0] = x
    fdivp ;st[0] = 1/x
    add esp, 8
    
    mov esp, ebp
    pop ebp
    ret
