section .text

global f1
global _f1
_f1:
f1:
    finit
    fld qword[esp + 4]
    frndint
    fld1
    fscale

    fld qword[esp + 4]
    fld qword[esp + 4]
    frndint
    fsubp
    f2xm1
    fld1
    faddp

    fmulp
    fld1
    faddp

    ret

global f2
global _f2
_f2:
f2:
   finit
   fld qword[esp + 4]
   fld qword[esp + 4]
   fmulp
   fld st0
   fmulp
   fld qword[esp + 4]
   fmulp
   ret

global f3
global _f3
_f3:
f3:
   finit
   fld1
   fld qword[esp + 4]
   fsubp
   fld1
   fld1
   faddp
   fld1
   faddp
   fdivp
   ret

global pf1
global _pf1
_pf1:
pf1:
    finit
    fld qword[esp + 4]
    frndint
    fld1
    fscale

    fld qword[esp + 4]
    fld qword[esp + 4]
    frndint
    fsubp
    f2xm1
    fld1
    faddp

    fmulp
    fldln2
    fmulp
    ret

global pf2
global _pf2
_pf2:
pf2:
    finit
    fld qword[esp + 4]
    fld qword[esp + 4]
    fmulp
    fld st0
    fmulp
    fld1
    fld1
    faddp
    fld st0
    faddp
    fld1
    faddp
    fmulp
    ret

global pf3
global _pf3
_pf3:
pf3:
    finit
    fldz
    fld1
    fsubp
    fld1
    fld1
    faddp
    fld1
    faddp
    fdivp
    ret


