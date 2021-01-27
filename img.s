/*
 * Function adds given value in range [-127, 127] to chosen channel of every pixel in img data matrix.
 * 
 * which_channel = (R = 1, G = 2, B = 3)
 */
 
.text
.global add_to_channel
.global puts

add_to_channel:
    mul r1, r2                    @ r1 = width * height
    add r0, r3                    
    sub r0, #1                    @ r0 = tab[which_channel - 1]
    ldrsb r3, [sp, #0]            @ r3 = value
    b for_condition
for_loop:
    ldrb r2, [r0, #0]             @ load value from matrix
    adds r2, r3    
    cmp r2, #0
    movlt r2, #0
    cmp r2, #255
    movgt r2, #255
    strb r2, [r0, #0]             @ store with added value
    add r0, #3                    @ tab += 3 (3 channels)
    sub r1, #1
for_condition:
    cmp r1, #0                    @ i == 0
    bgt for_loop
    bx lr                         @ return from main
