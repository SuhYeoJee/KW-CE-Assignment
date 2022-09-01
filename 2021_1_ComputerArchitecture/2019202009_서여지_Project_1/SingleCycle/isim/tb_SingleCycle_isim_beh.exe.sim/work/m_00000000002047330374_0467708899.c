/**********************************************************************/
/*   ____  ____                                                       */
/*  /   /\/   /                                                       */
/* /___/  \  /                                                        */
/* \   \   \/                                                       */
/*  \   \        Copyright (c) 2003-2009 Xilinx, Inc.                */
/*  /   /          All Right Reserved.                                 */
/* /---/   /\                                                         */
/* \   \  /  \                                                      */
/*  \___\/\___\                                                    */
/***********************************************************************/

/* This file is designed for use with ISim build 0x7708f090 */

#define XSI_HIDE_SYMBOL_SPEC true
#include "xsi.h"
#include <memory.h>
#ifdef __GNUC__
#include <stdlib.h>
#else
#include <malloc.h>
#define alloca _alloca
#endif
static const char *ng0 = "C:/Users/gun07/Documents/ISE/SingleCycle/SingleCycle.v";
static const char *ng1 = "INSTR_ROM.txt";
static int ng2[] = {0, 0};
static int ng3[] = {255, 0};
static unsigned int ng4[] = {0U, 0U};
static int ng5[] = {3, 0};
static int ng6[] = {7, 0};
static int ng7[] = {2, 0};
static int ng8[] = {15, 0};
static int ng9[] = {8, 0};
static int ng10[] = {1, 0};
static int ng11[] = {23, 0};
static int ng12[] = {16, 0};
static int ng13[] = {31, 0};
static int ng14[] = {24, 0};
static unsigned int ng15[] = {1U, 0U};



static void Initial_464_0(char *t0)
{
    char *t1;
    char *t2;
    char *t3;

LAB0:    xsi_set_current_line(464, ng0);

LAB2:    xsi_set_current_line(465, ng0);
    t1 = (t0 + 1608);
    t2 = ((char*)((ng2)));
    t3 = ((char*)((ng3)));
    xsi_vlogfile_readmemb(ng1, 0, t1, 1, *((unsigned int *)t2), 1, *((unsigned int *)t3));
    xsi_set_current_line(466, ng0);
    t1 = ((char*)((ng4)));
    t2 = (t0 + 1768);
    xsi_vlogvar_assign_value(t2, t1, 0, 0, 1);

LAB1:    return;
}

static void Always_469_1(char *t0)
{
    char t7[8];
    char t16[8];
    char t18[8];
    char t19[8];
    char t20[8];
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    char *t6;
    char *t8;
    char *t9;
    char *t10;
    char *t11;
    char *t12;
    char *t13;
    char *t14;
    char *t15;
    char *t17;
    char *t21;
    char *t22;
    char *t23;
    char *t24;
    char *t25;
    char *t26;
    unsigned int t27;
    int t28;
    char *t29;
    unsigned int t30;
    int t31;
    int t32;
    char *t33;
    unsigned int t34;
    int t35;
    int t36;
    unsigned int t37;
    int t38;
    unsigned int t39;
    unsigned int t40;
    int t41;
    int t42;

LAB0:    t1 = (t0 + 3256U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(469, ng0);
    t2 = (t0 + 3824);
    *((int *)t2) = 1;
    t3 = (t0 + 3288);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(469, ng0);

LAB5:    xsi_set_current_line(470, ng0);
    t4 = (t0 + 1608);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    t8 = (t0 + 1608);
    t9 = (t8 + 72U);
    t10 = *((char **)t9);
    t11 = (t0 + 1608);
    t12 = (t11 + 64U);
    t13 = *((char **)t12);
    t14 = (t0 + 1048U);
    t15 = *((char **)t14);
    t14 = ((char*)((ng5)));
    memset(t16, 0, 8);
    xsi_vlog_unsigned_add(t16, 32, t15, 32, t14, 32);
    xsi_vlog_generic_get_array_select_value(t7, 8, t6, t10, t13, 2, 1, t16, 32, 2);
    t17 = (t0 + 1448);
    t21 = (t0 + 1448);
    t22 = (t21 + 72U);
    t23 = *((char **)t22);
    t24 = ((char*)((ng6)));
    t25 = ((char*)((ng2)));
    xsi_vlog_convert_partindices(t18, t19, t20, ((int*)(t23)), 2, t24, 32, 1, t25, 32, 1);
    t26 = (t18 + 4);
    t27 = *((unsigned int *)t26);
    t28 = (!(t27));
    t29 = (t19 + 4);
    t30 = *((unsigned int *)t29);
    t31 = (!(t30));
    t32 = (t28 && t31);
    t33 = (t20 + 4);
    t34 = *((unsigned int *)t33);
    t35 = (!(t34));
    t36 = (t32 && t35);
    if (t36 == 1)
        goto LAB6;

LAB7:    xsi_set_current_line(471, ng0);
    t2 = (t0 + 1608);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t0 + 1608);
    t6 = (t5 + 72U);
    t8 = *((char **)t6);
    t9 = (t0 + 1608);
    t10 = (t9 + 64U);
    t11 = *((char **)t10);
    t12 = (t0 + 1048U);
    t13 = *((char **)t12);
    t12 = ((char*)((ng7)));
    memset(t16, 0, 8);
    xsi_vlog_unsigned_add(t16, 32, t13, 32, t12, 32);
    xsi_vlog_generic_get_array_select_value(t7, 8, t4, t8, t11, 2, 1, t16, 32, 2);
    t14 = (t0 + 1448);
    t15 = (t0 + 1448);
    t17 = (t15 + 72U);
    t21 = *((char **)t17);
    t22 = ((char*)((ng8)));
    t23 = ((char*)((ng9)));
    xsi_vlog_convert_partindices(t18, t19, t20, ((int*)(t21)), 2, t22, 32, 1, t23, 32, 1);
    t24 = (t18 + 4);
    t27 = *((unsigned int *)t24);
    t28 = (!(t27));
    t25 = (t19 + 4);
    t30 = *((unsigned int *)t25);
    t31 = (!(t30));
    t32 = (t28 && t31);
    t26 = (t20 + 4);
    t34 = *((unsigned int *)t26);
    t35 = (!(t34));
    t36 = (t32 && t35);
    if (t36 == 1)
        goto LAB8;

LAB9:    xsi_set_current_line(472, ng0);
    t2 = (t0 + 1608);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t0 + 1608);
    t6 = (t5 + 72U);
    t8 = *((char **)t6);
    t9 = (t0 + 1608);
    t10 = (t9 + 64U);
    t11 = *((char **)t10);
    t12 = (t0 + 1048U);
    t13 = *((char **)t12);
    t12 = ((char*)((ng10)));
    memset(t16, 0, 8);
    xsi_vlog_unsigned_add(t16, 32, t13, 32, t12, 32);
    xsi_vlog_generic_get_array_select_value(t7, 8, t4, t8, t11, 2, 1, t16, 32, 2);
    t14 = (t0 + 1448);
    t15 = (t0 + 1448);
    t17 = (t15 + 72U);
    t21 = *((char **)t17);
    t22 = ((char*)((ng11)));
    t23 = ((char*)((ng12)));
    xsi_vlog_convert_partindices(t18, t19, t20, ((int*)(t21)), 2, t22, 32, 1, t23, 32, 1);
    t24 = (t18 + 4);
    t27 = *((unsigned int *)t24);
    t28 = (!(t27));
    t25 = (t19 + 4);
    t30 = *((unsigned int *)t25);
    t31 = (!(t30));
    t32 = (t28 && t31);
    t26 = (t20 + 4);
    t34 = *((unsigned int *)t26);
    t35 = (!(t34));
    t36 = (t32 && t35);
    if (t36 == 1)
        goto LAB10;

LAB11:    xsi_set_current_line(473, ng0);
    t2 = (t0 + 1608);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t0 + 1608);
    t6 = (t5 + 72U);
    t8 = *((char **)t6);
    t9 = (t0 + 1608);
    t10 = (t9 + 64U);
    t11 = *((char **)t10);
    t12 = (t0 + 1048U);
    t13 = *((char **)t12);
    xsi_vlog_generic_get_array_select_value(t7, 8, t4, t8, t11, 2, 1, t13, 32, 2);
    t12 = (t0 + 1448);
    t14 = (t0 + 1448);
    t15 = (t14 + 72U);
    t17 = *((char **)t15);
    t21 = ((char*)((ng13)));
    t22 = ((char*)((ng14)));
    xsi_vlog_convert_partindices(t16, t18, t19, ((int*)(t17)), 2, t21, 32, 1, t22, 32, 1);
    t23 = (t16 + 4);
    t27 = *((unsigned int *)t23);
    t28 = (!(t27));
    t24 = (t18 + 4);
    t30 = *((unsigned int *)t24);
    t31 = (!(t30));
    t32 = (t28 && t31);
    t25 = (t19 + 4);
    t34 = *((unsigned int *)t25);
    t35 = (!(t34));
    t36 = (t32 && t35);
    if (t36 == 1)
        goto LAB12;

LAB13:    goto LAB2;

LAB6:    t37 = *((unsigned int *)t20);
    t38 = (t37 + 0);
    t39 = *((unsigned int *)t18);
    t40 = *((unsigned int *)t19);
    t41 = (t39 - t40);
    t42 = (t41 + 1);
    xsi_vlogvar_wait_assign_value(t17, t7, t38, *((unsigned int *)t19), t42, 0LL);
    goto LAB7;

LAB8:    t37 = *((unsigned int *)t20);
    t38 = (t37 + 0);
    t39 = *((unsigned int *)t18);
    t40 = *((unsigned int *)t19);
    t41 = (t39 - t40);
    t42 = (t41 + 1);
    xsi_vlogvar_wait_assign_value(t14, t7, t38, *((unsigned int *)t19), t42, 0LL);
    goto LAB9;

LAB10:    t37 = *((unsigned int *)t20);
    t38 = (t37 + 0);
    t39 = *((unsigned int *)t18);
    t40 = *((unsigned int *)t19);
    t41 = (t39 - t40);
    t42 = (t41 + 1);
    xsi_vlogvar_wait_assign_value(t14, t7, t38, *((unsigned int *)t19), t42, 0LL);
    goto LAB11;

LAB12:    t37 = *((unsigned int *)t19);
    t38 = (t37 + 0);
    t39 = *((unsigned int *)t16);
    t40 = *((unsigned int *)t18);
    t41 = (t39 - t40);
    t42 = (t41 + 1);
    xsi_vlogvar_wait_assign_value(t12, t7, t38, *((unsigned int *)t18), t42, 0LL);
    goto LAB13;

}

static void Always_476_2(char *t0)
{
    char t8[8];
    char t30[8];
    char t43[8];
    char t44[8];
    char t55[8];
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    char *t6;
    char *t7;
    char *t9;
    char *t10;
    unsigned int t11;
    unsigned int t12;
    unsigned int t13;
    unsigned int t14;
    unsigned int t15;
    unsigned int t16;
    unsigned int t17;
    unsigned int t18;
    unsigned int t19;
    unsigned int t20;
    unsigned int t21;
    unsigned int t22;
    char *t23;
    char *t24;
    unsigned int t25;
    unsigned int t26;
    unsigned int t27;
    unsigned int t28;
    unsigned int t29;
    char *t31;
    char *t32;
    char *t33;
    char *t34;
    char *t35;
    unsigned int t36;
    unsigned int t37;
    unsigned int t38;
    unsigned int t39;
    unsigned int t40;
    unsigned int t41;
    char *t42;
    char *t45;
    char *t46;
    char *t47;
    char *t48;
    char *t49;
    char *t50;
    char *t51;
    char *t52;
    char *t53;
    char *t54;
    char *t56;
    unsigned int t57;
    int t58;
    char *t59;
    unsigned int t60;
    int t61;
    int t62;
    unsigned int t63;
    unsigned int t64;
    int t65;
    int t66;

LAB0:    t1 = (t0 + 3504U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(476, ng0);
    t2 = (t0 + 3840);
    *((int *)t2) = 1;
    t3 = (t0 + 3536);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(476, ng0);

LAB5:    xsi_set_current_line(477, ng0);
    t4 = (t0 + 1768);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    t7 = ((char*)((ng15)));
    memset(t8, 0, 8);
    t9 = (t6 + 4);
    t10 = (t7 + 4);
    t11 = *((unsigned int *)t6);
    t12 = *((unsigned int *)t7);
    t13 = (t11 ^ t12);
    t14 = *((unsigned int *)t9);
    t15 = *((unsigned int *)t10);
    t16 = (t14 ^ t15);
    t17 = (t13 | t16);
    t18 = *((unsigned int *)t9);
    t19 = *((unsigned int *)t10);
    t20 = (t18 | t19);
    t21 = (~(t20));
    t22 = (t17 & t21);
    if (t22 != 0)
        goto LAB9;

LAB6:    if (t20 != 0)
        goto LAB8;

LAB7:    *((unsigned int *)t8) = 1;

LAB9:    t24 = (t8 + 4);
    t25 = *((unsigned int *)t24);
    t26 = (~(t25));
    t27 = *((unsigned int *)t8);
    t28 = (t27 & t26);
    t29 = (t28 != 0);
    if (t29 > 0)
        goto LAB10;

LAB11:
LAB12:    goto LAB2;

LAB8:    t23 = (t8 + 4);
    *((unsigned int *)t8) = 1;
    *((unsigned int *)t23) = 1;
    goto LAB9;

LAB10:    xsi_set_current_line(477, ng0);

LAB13:    xsi_set_current_line(478, ng0);
    t31 = (t0 + 2088);
    t32 = (t31 + 56U);
    t33 = *((char **)t32);
    memset(t30, 0, 8);
    t34 = (t30 + 4);
    t35 = (t33 + 4);
    t36 = *((unsigned int *)t33);
    t37 = (t36 >> 0);
    *((unsigned int *)t30) = t37;
    t38 = *((unsigned int *)t35);
    t39 = (t38 >> 0);
    *((unsigned int *)t34) = t39;
    t40 = *((unsigned int *)t30);
    *((unsigned int *)t30) = (t40 & 255U);
    t41 = *((unsigned int *)t34);
    *((unsigned int *)t34) = (t41 & 255U);
    t42 = (t0 + 1608);
    t45 = (t0 + 1608);
    t46 = (t45 + 72U);
    t47 = *((char **)t46);
    t48 = (t0 + 1608);
    t49 = (t48 + 64U);
    t50 = *((char **)t49);
    t51 = (t0 + 1928);
    t52 = (t51 + 56U);
    t53 = *((char **)t52);
    t54 = ((char*)((ng5)));
    memset(t55, 0, 8);
    xsi_vlog_unsigned_add(t55, 32, t53, 32, t54, 32);
    xsi_vlog_generic_convert_array_indices(t43, t44, t47, t50, 2, 1, t55, 32, 2);
    t56 = (t43 + 4);
    t57 = *((unsigned int *)t56);
    t58 = (!(t57));
    t59 = (t44 + 4);
    t60 = *((unsigned int *)t59);
    t61 = (!(t60));
    t62 = (t58 && t61);
    if (t62 == 1)
        goto LAB14;

LAB15:    xsi_set_current_line(479, ng0);
    t2 = (t0 + 2088);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    memset(t8, 0, 8);
    t5 = (t8 + 4);
    t6 = (t4 + 4);
    t11 = *((unsigned int *)t4);
    t12 = (t11 >> 8);
    *((unsigned int *)t8) = t12;
    t13 = *((unsigned int *)t6);
    t14 = (t13 >> 8);
    *((unsigned int *)t5) = t14;
    t15 = *((unsigned int *)t8);
    *((unsigned int *)t8) = (t15 & 255U);
    t16 = *((unsigned int *)t5);
    *((unsigned int *)t5) = (t16 & 255U);
    t7 = (t0 + 1608);
    t9 = (t0 + 1608);
    t10 = (t9 + 72U);
    t23 = *((char **)t10);
    t24 = (t0 + 1608);
    t31 = (t24 + 64U);
    t32 = *((char **)t31);
    t33 = (t0 + 1928);
    t34 = (t33 + 56U);
    t35 = *((char **)t34);
    t42 = ((char*)((ng7)));
    memset(t44, 0, 8);
    xsi_vlog_unsigned_add(t44, 32, t35, 32, t42, 32);
    xsi_vlog_generic_convert_array_indices(t30, t43, t23, t32, 2, 1, t44, 32, 2);
    t45 = (t30 + 4);
    t17 = *((unsigned int *)t45);
    t58 = (!(t17));
    t46 = (t43 + 4);
    t18 = *((unsigned int *)t46);
    t61 = (!(t18));
    t62 = (t58 && t61);
    if (t62 == 1)
        goto LAB16;

LAB17:    xsi_set_current_line(480, ng0);
    t2 = (t0 + 2088);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    memset(t8, 0, 8);
    t5 = (t8 + 4);
    t6 = (t4 + 4);
    t11 = *((unsigned int *)t4);
    t12 = (t11 >> 16);
    *((unsigned int *)t8) = t12;
    t13 = *((unsigned int *)t6);
    t14 = (t13 >> 16);
    *((unsigned int *)t5) = t14;
    t15 = *((unsigned int *)t8);
    *((unsigned int *)t8) = (t15 & 255U);
    t16 = *((unsigned int *)t5);
    *((unsigned int *)t5) = (t16 & 255U);
    t7 = (t0 + 1608);
    t9 = (t0 + 1608);
    t10 = (t9 + 72U);
    t23 = *((char **)t10);
    t24 = (t0 + 1608);
    t31 = (t24 + 64U);
    t32 = *((char **)t31);
    t33 = (t0 + 1928);
    t34 = (t33 + 56U);
    t35 = *((char **)t34);
    t42 = ((char*)((ng10)));
    memset(t44, 0, 8);
    xsi_vlog_unsigned_add(t44, 32, t35, 32, t42, 32);
    xsi_vlog_generic_convert_array_indices(t30, t43, t23, t32, 2, 1, t44, 32, 2);
    t45 = (t30 + 4);
    t17 = *((unsigned int *)t45);
    t58 = (!(t17));
    t46 = (t43 + 4);
    t18 = *((unsigned int *)t46);
    t61 = (!(t18));
    t62 = (t58 && t61);
    if (t62 == 1)
        goto LAB18;

LAB19:    xsi_set_current_line(481, ng0);
    t2 = (t0 + 2088);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    memset(t8, 0, 8);
    t5 = (t8 + 4);
    t6 = (t4 + 4);
    t11 = *((unsigned int *)t4);
    t12 = (t11 >> 24);
    *((unsigned int *)t8) = t12;
    t13 = *((unsigned int *)t6);
    t14 = (t13 >> 24);
    *((unsigned int *)t5) = t14;
    t15 = *((unsigned int *)t8);
    *((unsigned int *)t8) = (t15 & 255U);
    t16 = *((unsigned int *)t5);
    *((unsigned int *)t5) = (t16 & 255U);
    t7 = (t0 + 1608);
    t9 = (t0 + 1608);
    t10 = (t9 + 72U);
    t23 = *((char **)t10);
    t24 = (t0 + 1608);
    t31 = (t24 + 64U);
    t32 = *((char **)t31);
    t33 = (t0 + 1928);
    t34 = (t33 + 56U);
    t35 = *((char **)t34);
    xsi_vlog_generic_convert_array_indices(t30, t43, t23, t32, 2, 1, t35, 32, 2);
    t42 = (t30 + 4);
    t17 = *((unsigned int *)t42);
    t58 = (!(t17));
    t45 = (t43 + 4);
    t18 = *((unsigned int *)t45);
    t61 = (!(t18));
    t62 = (t58 && t61);
    if (t62 == 1)
        goto LAB20;

LAB21:    goto LAB12;

LAB14:    t63 = *((unsigned int *)t43);
    t64 = *((unsigned int *)t44);
    t65 = (t63 - t64);
    t66 = (t65 + 1);
    xsi_vlogvar_wait_assign_value(t42, t30, 0, *((unsigned int *)t44), t66, 0LL);
    goto LAB15;

LAB16:    t19 = *((unsigned int *)t30);
    t20 = *((unsigned int *)t43);
    t65 = (t19 - t20);
    t66 = (t65 + 1);
    xsi_vlogvar_wait_assign_value(t7, t8, 0, *((unsigned int *)t43), t66, 0LL);
    goto LAB17;

LAB18:    t19 = *((unsigned int *)t30);
    t20 = *((unsigned int *)t43);
    t65 = (t19 - t20);
    t66 = (t65 + 1);
    xsi_vlogvar_wait_assign_value(t7, t8, 0, *((unsigned int *)t43), t66, 0LL);
    goto LAB19;

LAB20:    t19 = *((unsigned int *)t30);
    t20 = *((unsigned int *)t43);
    t65 = (t19 - t20);
    t66 = (t65 + 1);
    xsi_vlogvar_wait_assign_value(t7, t8, 0, *((unsigned int *)t43), t66, 0LL);
    goto LAB21;

}


extern void work_m_00000000002047330374_0467708899_init()
{
	static char *pe[] = {(void *)Initial_464_0,(void *)Always_469_1,(void *)Always_476_2};
	xsi_register_didat("work_m_00000000002047330374_0467708899", "isim/tb_SingleCycle_isim_beh.exe.sim/work/m_00000000002047330374_0467708899.didat");
	xsi_register_executes(pe);
}
