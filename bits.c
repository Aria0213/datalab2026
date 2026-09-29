 /* WARNING: Do not include any other libraries here,
 * otherwise you will get an error while running test.py
 * You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 *
 * Using printf will interfere with our script capturing the execution results.
 * At this point, you can only test correctness with ./btest.
 * After confirming everything is correct in ./btest, remove the printf
 * and run the complete tests with test.py.
 */

 /*
 * bitAnd - x & y using only ~ and |
 * Example: bitAnd(4, 5) = 4
 * Legal ops: ~ |
 * Max ops: 7
 * Difficulty: 1
 */
int bitAnd(int x, int y) {
    return ~((~x)|(~y));
}

/*
 * bitXor - x ^ y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 7
 *   Difficulty: 1
 */
int bitXor(int x, int y) {
    return ~(~x&~y)&~(x&y) ;
}

/*
 * samesign - Determines if two integers have the same sign.
 *   0 is not positive, nor negative
 *   Example: samesign(0, 1) = 0, samesign(0, 0) = 1
 *            samesign(-4, -5) = 1, samesign(-4, 5) = 0
 *   Legal ops: >> << ! ^ && if else &
 *   Max ops: 12
 *   Difficulty: 2
 *
 * Parameters:
 *   x - The first integer.
 *   y - The second integer.
 *
 * Returns:
 *   1 if x and y have the same sign , 0 otherwise.
 */
int samesign(int x, int y) {
    if(!(x&&y))return (!x)&&(!y);
    int x_sign=(x>>31)&1;
    int y_sign=(y>>31)&1;
    return !(x_sign^y_sign);
}

/*
 * logtwo - Calculate the base-2 logarithm of a positive integer using bit
 *   shifting. (Think about bitCount)
 *   Note: You may assume that v > 0
 *   Example: logtwo(32) = 5
 *   Legal ops: > < >> << |
 *   Max ops: 25
 *   Difficulty: 4
 */
int logtwo(int v) {
    int b16=(v>>16)>0;
    int r16=b16<<4;
    v=v>>r16;
    int b8=(v>>8)>0;
    int r8=b8<<3;
    v=v>>r8;
    int b4=(v>>4)>0;
    int r4=b4<<2;
    v=v>>r4;
    int b2=(v>>2)>0;
    int r2=b2<<1;
    v=v>>r2;
    int b1=(v>>1)>0;
    int r1=b1;
    v=v>>r1;
    return r16|r8|r4|r2|r1;
}

/*
 *  byteSwap - swaps the nth byte and the mth byte
 *    Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *              byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *    Note: You may assume that 0 <= n <= 3, 0 <= m <= 3
 *    Legal ops: ! ~ & ^ | + << >>
 *    Max ops: 17
 *    Difficulty: 2
 */
int byteSwap(int x, int n, int m) {
    n=n<<3;
    m=m<<3;
    int n_byte=(x>>n)&0xFF;
    int m_byte=(x>>m)&0xFF;
    int clear=~((0xFF<<n)^(0xFF<<m));
    x=x&clear;
    x=x|(m_byte<<n);
    x=x|(n_byte<<m);
    return x;
}

/*
 * reverse - Reverse the bit order of a 32-bit unsigned integer.
 *   Example: reverse(0xFFFF0000) = 0x0000FFFF reverse(0x80000000)=0x1 reverse(0xA0000000)=0x5
 *   Note: You may assume that an unsigned integer is 32 bits long.
 *   Legal ops: << | & - + >> for while ! ~ (You can define unsigned in this function)
 *   Max ops: 30
 *   Difficulty: 3
 */
unsigned reverse(unsigned v) {
    unsigned res=0;
    res+=(v&1)<<31;
    unsigned i=1;
    while(i&31){
        unsigned r=(v>>i)&1;
        res+=r<<(31-i);
        i=i+1;
    }
    return res;
}

/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Note: You can assume that 0 <= n <= 31
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Difficulty: 3
 */
int logicalShift(int x, int n) {
    int mask=~((~0<<1)<<(31+(~n+1)));
    return (x>>n)&mask;
}

/*
 * leftBitCount - returns count of number of consective 1's in left-hand (most) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12,
 *             leftBitCount(0xFE00FF0F) = 7
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Difficulty: 4
 */
int leftBitCount(int x) { 
    int r16=(!~(x>>16))<<4;
    x=x<<r16;
    int r8=(!~(x>>24))<<3;
    x=x<<r8;
    int r4=(!~(x>>28))<<2;
    x=x<<r4;
    int r2=(!~(x>>30))<<1;
    x=x<<r2;
    int r1=(x>>31)&1;
    x=x<<r1;
    return (r16|r8|r4|r2|r1)+((x>>31)&1);
}

/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but it is to be interpreted as
 *   the bit-level representation of a single-precision floating point values.
 *   Legal ops: if else while for & | ~ + - >> << < > ! ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned float_i2f(int x) {
    unsigned sign=x&0x80000000;
    unsigned co=x;
    if(x==0)return 0;
    if(sign)co=-co;
    unsigned temp=co;
    int e=0;
    while(temp>>1){
        temp=temp>>1;
        e++;
    }
    if(e<24){
        unsigned fra=(co<<(23-e))&0x7FFFFF;
        return sign|(e+127)<<23|fra;
    }else{
        int shift=e-23;
        unsigned kept=co>>shift;
        unsigned lost=co&((1u<<shift)-1);
        unsigned half=1u<<(shift-1);
        if(lost>half)kept=kept+1;
        if(lost==half){
            if(kept&1)kept=kept+1;
        }
        return sign|(((e+126)<<23)+kept);
    }
}

/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: & >> << | if > < >= <= ! ~ else + ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatScale2(unsigned uf) {
    unsigned sign = uf & 0x80000000;
    unsigned exponent = uf & 0x7F800000;
    unsigned fraction = uf & 0x7FFFFF;

    if (exponent == 0x7F800000) return uf;
    if (!exponent) return sign | (fraction << 1);

    exponent = exponent + 0x800000;
    if (exponent == 0x7F800000) fraction = 0;
    return sign | exponent | fraction;
}

/*
 * float64_f2i - Convert a 64-bit IEEE 754 floating-point number to a 32-bit signed integer.
 *   The conversion rounds towards zero.
 *   Note: Assumes IEEE 754 representation and standard two's complement integer format.
 *   Parameters:
 *     uf1 - The lower 32 bits of the 64-bit floating-point number.
 *     uf2 - The higher 32 bits of the 64-bit floating-point number.
 *   Returns:
 *     The converted integer value, or 0x80000000 on overflow, or 0 on underflow.
 *   Legal ops: >> << | & ~ ! + - > < >= <= if else
 *   Max ops: 60
 *   Difficulty: 3
 */
int float64_f2i(unsigned uf1, unsigned uf2) {
    int e = (uf2 >> 20) & 0x7FF;
    unsigned sign = uf2 >> 31;
    unsigned total;
    int res;

    e = e - 1023;
    if (e < 0) return 0;
    /* INT_MIN has the same encoding as the overflow sentinel. */
    if (e >= 31) return 0x80000000;

    /* Keep the leading 32 significand bits, including the implicit 1. */
    total = (((uf2 & 0xFFFFF) | 0x100000) << 11) | (uf1 >> 21);
    res = total >> (31 - e);
    if (sign) return -res;
    return res;
}

/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: < > <= >= << >> + - & | ~ ! if else &&
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatPower2(int x) {
    if (x < -149) return 0;
    if (x < -126) return 1u << (x + 149);
    if (x > 127) return 0x7F800000;
    return (x + 127) << 23;
}
