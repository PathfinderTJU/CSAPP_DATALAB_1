/*
 * CS:APP Data Lab
 *
 * 3017218063 liuxingyu
 *
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:

  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code
  must conform to the following style:

  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>

  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.


  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function.
     The max operator count is checked by dlc. Note that '=' is not
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 *
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce
 *      the correct answers.
 */


#endif
/*
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
    /*
     *本函数的作用为：判断一个数x是否落在0x30-0x39（十进制47-58）
     *思路：
     *  1. 上界检查：若x落在区间内，则（0x39-x）的值应该>=0
     *  2. 下界检查：若x落在区间内，则（x-0x30）的值应该>=0
     *  3. 同时符合上界、下界检查的即满足要求，返回1，否则返回0.
     */
    int top = 0x39 + (~x) + 1;              // top = 0x39-x
    int bottom = x + (~0x30) + 1;           // bottom = x-0x30

    /*
     *右移31位（int长为32位），将top所有位置为与符号位相同。
     *若top>=0, 结果为0x00000000（十进制0），否则。结果为0xFFFFFFFF（十进制-1）
     */
    int check_top = top >> 31;
    int check_bottom = bottom >> 31;

    /*
     *若x落在规定范围内，则check_top和check_bottom均为0。则按位或的结果为0，再取反，输出1。
     *若x不在规定范围内，则check_top和check_bottom至少一个为0。则按位或的结果不为0，再取反，输出0。
     */
    return !(check_top | check_bottom);
}
/*
 * anyEvenBit - return 1 if any even-numbered bit in word set to 1
 *   Examples anyEvenBit(0xA) = 0, anyEvenBit(0xE) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int anyEvenBit(int x) {
    /*
     *本函数的作用为：当x任意偶数位为1时返回1，否则返回0。
     *思路：
     *  将x与0x55555555（偶数位均为1）进行按位与。当x所有偶数位均为0时，结果为0，否则结果不为0。
     */

    /*
     *由于只允许使用0-255之间的偶数，所以下面两行用于构造0x55555555
     *先将0x55右移8位，变为0x5500，将它与0x55按位或，得到0x5555
     *同理，构造0x55555555
     */
    int check = 0x55 | 0x55 << 8;
    check = check | check << 16;

     //x与check进行按位与。！！两次取反用于将整数结果转化为对应的布尔值。即非0数->1,0->0.
    return !!(x & check);

}
/*
 * copyLSB - set all bits of result to least significant bit of x
 *   Example: copyLSB(5) = 0xFFFFFFFF, copyLSB(6) = 0x00000000
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int copyLSB(int x) {
    /*
     *本函数用于将x所有位置为第0位的值。
     *思路：
     *  1. 将x左移31位（int为32位），将第0位移至符号位，其余位为0。
     *  2. 再将x右移31位，因为符号位为原第0位，所以根据逻辑右移的规则，所有位都会被填充为符号位的值，即完成需求。
     */
    return (x << 31) >> 31;
}
/*
 * leastBitPos - return a mask that marks the position of the
 *               least significant 1 bit. If x == 0, return 0
 *   Example: leastBitPos(96) = 0x20
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int leastBitPos(int x) {
    /*
     *本函数返回一个掩码，在该掩码中标识了二进制数x的所有位中，1所在的位权最小的位（其它所有位为0）
     *思路：
     *  1. 设1所在位权最小的位为n。先将x-1，则可将第n位置为0,0~n-1位置为1。
     *  2. 将x-1与x进行按位异或。则n+1~31位被置为0（相同），0~n位被置为1（不同）。
     *  3. 将2中结果与x进行按位与，则只有第n位为1。
     */
    int temp = x + (~1) + 1;                //temp=x-1
    return ( temp^x ) & x;
}
/*
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int divpwr2(int x, int n) {
    /*
     *本函数用于计算（x/2^n)的值
     *思路：
     *  x/2^n实质上等于x进行逻辑右移后的值（向0取整）。但若x为负数，则应该加上一个偏移量bias来修正舍入问题。
     */
    int flag = x >> 31;                         //判断x正负，若x为正，flag为0，否则flag为-1
    int bias = (flag << 0) + (~(flag << n)+1);  //bias = (2^n-1)*flag。即x为正，偏移量为0，x为负，偏移量为2^n-1
    return ((x + bias) >> n);
}

/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>

 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
    /*
     *本函数用于计算二进制数x中1的总位数。
     *思路：采用分治的思想
     *  1. 将32bit的整数x每两bit分为一组。对于两bit的数，其中1的个数等于两位相加所得的二进制数。
     *     例如：00：0+0 = 00（0），01:0+1 = 01（1）
     *           10: 1+0 = 01（0），11:1+1 = 10（2）
     *     对于一个两bit的数n，n&01与（n>>1）&01的和即为n两位之和。
     *     因此，对x的每一组2bit数进行如上操作，并将结果储存在对应的两位中。即x&0x55555555 + （x>>1）&0x55555555
     *  2. 将相邻的2bit组合并为4bit组，x被分为8组。
     *     在一组4bit数中，前两位为一个计算结果，后两位为一个计算结果，将它们的值相加即为4bit中1的个数
     *     例如：对于1001，01为原数中前两位1的个数（1），10为原数中后两位1的个数（2），相加为0011即为原数中这四位1的个数
     *           过程为：1001 & 0011 + （1001 >> 2）&0011
     *     因此。对x的每一组4bit数进行如上操作，并将结果储存在对应的四位中。即x&0x33333333 + （x>>2）&0x33333333
     *  3. 继续合并，重复上述操作。
     *     第三次合并为8bit一组，辅助数为0x0f0f0f0f
     *     第四次合并为16bit一组，辅助数为0x00ff00ff
     *     第五次合并为32bit一组，辅助数为0x0000ffff
     */

    /*
     *下面的代码为获取0x55555555,0x33333333,0x0f0f0f0f,0x00ff00ff,0x0000ffff
     */
    int temp1 = 0x55 | (0x55 << 8);
    int temp2 = 0x33 | (0x33 << 8);
    int temp3 = 0x0f | (0x0f << 8);
    int temp4 = 0xff | (0xff << 16);
    int temp5 = ~((~0) & ((~0) << 16));

    temp1 = temp1 | (temp1 << 16);
    temp2 = temp2 | (temp2 << 16);
    temp3 = temp3 | (temp3 << 16);

    x = (x & temp1) + ((x >> 1) & temp1);
    x = (x & temp2) + ((x >> 2) & temp2);
    x = (x & temp3) + ((x >> 4) & temp3);
    x = (x & temp4) + ((x >> 8) & temp4);
    x = (x & temp5) + ((x >>16) & temp5);

    return x;
}
