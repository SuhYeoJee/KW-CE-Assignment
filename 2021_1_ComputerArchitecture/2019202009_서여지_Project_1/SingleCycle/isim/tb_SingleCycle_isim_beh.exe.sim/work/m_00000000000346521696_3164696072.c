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
static unsigned int ng1[] = {0U, 0U};
static unsigned int ng2[] = {9U, 0U};
static unsigned int ng3[] = {10U, 0U};
static unsigned int ng4[] = {11U, 0U};
static unsigned int ng5[] = {12U, 0U};
static unsigned int ng6[] = {18U, 0U};
static unsigned int ng7[] = {19U, 0U};



static void Always_274_0(char *t0)
{
    char t4[8];
    char t28[16];
    char t29[16];
    char t31[16];
    char t34[8];
    char t35[8];
    char *t1;
    char *t2;
    char *t3;
    char *t5;
    char *t6;
    unsigned int t7;
    unsigned int t8;
    unsigned int t9;
    unsigned int t10;
    unsigned int t11;
    char *t12;
    char *t13;
    unsigned int t14;
    unsigned int t15;
    unsigned int t16;
    unsigned int t17;
    unsigned int t18;
    char *t19;
    char *t20;
    unsigned int t21;
    unsigned int t22;
    unsigned int t23;
    unsigned int t24;
    unsigned int t25;
    unsigned int t26;
    unsigned int t27;
    char *t30;
    char *t32;

LAB0:    t1 = (t0 + 3168U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(274, ng0);
    t2 = (t0 + 3488);
    *((int *)t2) = 1;
    t3 = (t0 + 3200);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(274, ng0);

LAB5:    xsi_set_current_line(275, ng0);
    t5 = (t0 + 1208U);
    t6 = *((char **)t5);
    memset(t4, 0, 8);
    t5 = (t6 + 4);
    t7 = *((unsigned int *)t5);
    t8 = (~(t7));
    t9 = *((unsigned int *)t6);
    t10 = (t9 & t8);
    t11 = (t10 & 1U);
    if (t11 != 0)
        goto LAB9;

LAB7:    if (*((unsigned int *)t5) == 0)
        goto LAB6;

LAB8:    t12 = (t4 + 4);
    *((unsigned int *)t4) = 1;
    *((unsigned int *)t12) = 1;

LAB9:    t13 = (t4 + 4);
    t14 = *((unsigned int *)t13);
    t15 = (~(t14));
    t16 = *((unsigned int *)t4);
    t17 = (t16 & t15);
    t18 = (t17 != 0);
    if (t18 > 0)
        goto LAB10;

LAB11:    xsi_set_current_line(279, ng0);

LAB14:    xsi_set_current_line(280, ng0);
    t2 = (t0 + 1688U);
    t3 = *((char **)t2);
    t2 = ((char*)((ng2)));
    memset(t4, 0, 8);
    t5 = (t3 + 4);
    t6 = (t2 + 4);
    t7 = *((unsigned int *)t3);
    t8 = *((unsigned int *)t2);
    t9 = (t7 ^ t8);
    t10 = *((unsigned int *)t5);
    t11 = *((unsigned int *)t6);
    t14 = (t10 ^ t11);
    t15 = (t9 | t14);
    t16 = *((unsigned int *)t5);
    t17 = *((unsigned int *)t6);
    t18 = (t16 | t17);
    t21 = (~(t18));
    t22 = (t15 & t21);
    if (t22 != 0)
        goto LAB18;

LAB15:    if (t18 != 0)
        goto LAB17;

LAB16:    *((unsigned int *)t4) = 1;

LAB18:    t13 = (t4 + 4);
    t23 = *((unsigned int *)t13);
    t24 = (~(t23));
    t25 = *((unsigned int *)t4);
    t26 = (t25 & t24);
    t27 = (t26 != 0);
    if (t27 > 0)
        goto LAB19;

LAB20:    xsi_set_current_line(283, ng0);
    t2 = (t0 + 1688U);
    t3 = *((char **)t2);
    t2 = ((char*)((ng3)));
    memset(t4, 0, 8);
    t5 = (t3 + 4);
    t6 = (t2 + 4);
    t7 = *((unsigned int *)t3);
    t8 = *((unsigned int *)t2);
    t9 = (t7 ^ t8);
    t10 = *((unsigned int *)t5);
    t11 = *((unsigned int *)t6);
    t14 = (t10 ^ t11);
    t15 = (t9 | t14);
    t16 = *((unsigned int *)t5);
    t17 = *((unsigned int *)t6);
    t18 = (t16 | t17);
    t21 = (~(t18));
    t22 = (t15 & t21);
    if (t22 != 0)
        goto LAB26;

LAB23:    if (t18 != 0)
        goto LAB25;

LAB24:    *((unsigned int *)t4) = 1;

LAB26:    t13 = (t4 + 4);
    t23 = *((unsigned int *)t13);
    t24 = (~(t23));
    t25 = *((unsigned int *)t4);
    t26 = (t25 & t24);
    t27 = (t26 != 0);
    if (t27 > 0)
        goto LAB27;

LAB28:    xsi_set_current_line(286, ng0);
    t2 = (t0 + 1688U);
    t3 = *((char **)t2);
    t2 = ((char*)((ng4)));
    memset(t4, 0, 8);
    t5 = (t3 + 4);
    t6 = (t2 + 4);
    t7 = *((unsigned int *)t3);
    t8 = *((unsigned int *)t2);
    t9 = (t7 ^ t8);
    t10 = *((unsigned int *)t5);
    t11 = *((unsigned int *)t6);
    t14 = (t10 ^ t11);
    t15 = (t9 | t14);
    t16 = *((unsigned int *)t5);
    t17 = *((unsigned int *)t6);
    t18 = (t16 | t17);
    t21 = (~(t18));
    t22 = (t15 & t21);
    if (t22 != 0)
        goto LAB34;

LAB31:    if (t18 != 0)
        goto LAB33;

LAB32:    *((unsigned int *)t4) = 1;

LAB34:    t13 = (t4 + 4);
    t23 = *((unsigned int *)t13);
    t24 = (~(t23));
    t25 = *((unsigned int *)t4);
    t26 = (t25 & t24);
    t27 = (t26 != 0);
    if (t27 > 0)
        goto LAB35;

LAB36:    xsi_set_current_line(290, ng0);
    t2 = (t0 + 1688U);
    t3 = *((char **)t2);
    t2 = ((char*)((ng5)));
    memset(t4, 0, 8);
    t5 = (t3 + 4);
    t6 = (t2 + 4);
    t7 = *((unsigned int *)t3);
    t8 = *((unsigned int *)t2);
    t9 = (t7 ^ t8);
    t10 = *((unsigned int *)t5);
    t11 = *((unsigned int *)t6);
    t14 = (t10 ^ t11);
    t15 = (t9 | t14);
    t16 = *((unsigned int *)t5);
    t17 = *((unsigned int *)t6);
    t18 = (t16 | t17);
    t21 = (~(t18));
    t22 = (t15 & t21);
    if (t22 != 0)
        goto LAB42;

LAB39:    if (t18 != 0)
        goto LAB41;

LAB40:    *((unsigned int *)t4) = 1;

LAB42:    t13 = (t4 + 4);
    t23 = *((unsigned int *)t13);
    t24 = (~(t23));
    t25 = *((unsigned int *)t4);
    t26 = (t25 & t24);
    t27 = (t26 != 0);
    if (t27 > 0)
        goto LAB43;

LAB44:    xsi_set_current_line(294, ng0);
    t2 = (t0 + 1688U);
    t3 = *((char **)t2);
    t2 = ((char*)((ng6)));
    memset(t4, 0, 8);
    t5 = (t3 + 4);
    t6 = (t2 + 4);
    t7 = *((unsigned int *)t3);
    t8 = *((unsigned int *)t2);
    t9 = (t7 ^ t8);
    t10 = *((unsigned int *)t5);
    t11 = *((unsigned int *)t6);
    t14 = (t10 ^ t11);
    t15 = (t9 | t14);
    t16 = *((unsigned int *)t5);
    t17 = *((unsigned int *)t6);
    t18 = (t16 | t17);
    t21 = (~(t18));
    t22 = (t15 & t21);
    if (t22 != 0)
        goto LAB50;

LAB47:    if (t18 != 0)
        goto LAB49;

LAB48:    *((unsigned int *)t4) = 1;

LAB50:    t13 = (t4 + 4);
    t23 = *((unsigned int *)t13);
    t24 = (~(t23));
    t25 = *((unsigned int *)t4);
    t26 = (t25 & t24);
    t27 = (t26 != 0);
    if (t27 > 0)
        goto LAB51;

LAB52:    xsi_set_current_line(298, ng0);
    t2 = (t0 + 1688U);
    t3 = *((char **)t2);
    t2 = ((char*)((ng7)));
    memset(t4, 0, 8);
    t5 = (t3 + 4);
    t6 = (t2 + 4);
    t7 = *((unsigned int *)t3);
    t8 = *((unsigned int *)t2);
    t9 = (t7 ^ t8);
    t10 = *((unsigned int *)t5);
    t11 = *((unsigned int *)t6);
    t14 = (t10 ^ t11);
    t15 = (t9 | t14);
    t16 = *((unsigned int *)t5);
    t17 = *((unsigned int *)t6);
    t18 = (t16 | t17);
    t21 = (~(t18));
    t22 = (t15 & t21);
    if (t22 != 0)
        goto LAB58;

LAB55:    if (t18 != 0)
        goto LAB57;

LAB56:    *((unsigned int *)t4) = 1;

LAB58:    t13 = (t4 + 4);
    t23 = *((unsigned int *)t13);
    t24 = (~(t23));
    t25 = *((unsigned int *)t4);
    t26 = (t25 & t24);
    t27 = (t26 != 0);
    if (t27 > 0)
        goto LAB59;

LAB60:    xsi_set_current_line(302, ng0);

LAB63:    xsi_set_current_line(303, ng0);
    t2 = (t0 + 2248);
    t3 = (t2 + 56U);
    t5 = *((char **)t3);
    t6 = (t0 + 2248);
    xsi_vlogvar_wait_assign_value(t6, t5, 0, 0, 32, 0LL);
    xsi_set_current_line(304, ng0);
    t2 = (t0 + 2088);
    t3 = (t2 + 56U);
    t5 = *((char **)t3);
    t6 = (t0 + 2088);
    xsi_vlogvar_wait_assign_value(t6, t5, 0, 0, 32, 0LL);

LAB61:
LAB53:
LAB45:
LAB37:
LAB29:
LAB21:
LAB12:    goto LAB2;

LAB6:    *((unsigned int *)t4) = 1;
    goto LAB9;

LAB10:    xsi_set_current_line(275, ng0);

LAB13:    xsi_set_current_line(276, ng0);
    t19 = ((char*)((ng1)));
    t20 = (t0 + 2088);
    xsi_vlogvar_wait_assign_value(t20, t19, 0, 0, 32, 0LL);
    xsi_set_current_line(277, ng0);
    t2 = ((char*)((ng1)));
    t3 = (t0 + 2248);
    xsi_vlogvar_wait_assign_value(t3, t2, 0, 0, 32, 0LL);
    goto LAB12;

LAB17:    t12 = (t4 + 4);
    *((unsigned int *)t4) = 1;
    *((unsigned int *)t12) = 1;
    goto LAB18;

LAB19:    xsi_set_current_line(280, ng0);

LAB22:    xsi_set_current_line(281, ng0);
    t19 = (t0 + 1368U);
    t20 = *((char **)t19);
    xsi_vlogtype_sign_extend(t28, 64, t20, 32);
    t19 = (t0 + 1528U);
    t30 = *((char **)t19);
    xsi_vlogtype_sign_extend(t29, 64, t30, 32);
    xsi_vlog_signed_multiply(t31, 64, t28, 64, t29, 64);
    t19 = (t0 + 2248);
    xsi_vlogvar_wait_assign_value(t19, t31, 0, 0, 32, 0LL);
    t32 = (t0 + 2088);
    xsi_vlogvar_wait_assign_value(t32, t31, 32, 0, 32, 0LL);
    goto LAB21;

LAB25:    t12 = (t4 + 4);
    *((unsigned int *)t4) = 1;
    *((unsigned int *)t12) = 1;
    goto LAB26;

LAB27:    xsi_set_current_line(283, ng0);

LAB30:    xsi_set_current_line(284, ng0);
    t19 = (t0 + 1368U);
    t20 = *((char **)t19);
    xsi_vlogtype_zero_extend(t28, 64, t20, 32);
    t19 = (t0 + 1528U);
    t30 = *((char **)t19);
    xsi_vlogtype_zero_extend(t29, 64, t30, 32);
    xsi_vlog_unsigned_multiply(t31, 64, t28, 64, t29, 64);
    t19 = (t0 + 2248);
    xsi_vlogvar_wait_assign_value(t19, t31, 0, 0, 32, 0LL);
    t32 = (t0 + 2088);
    xsi_vlogvar_wait_assign_value(t32, t31, 32, 0, 32, 0LL);
    goto LAB29;

LAB33:    t12 = (t4 + 4);
    *((unsigned int *)t4) = 1;
    *((unsigned int *)t12) = 1;
    goto LAB34;

LAB35:    xsi_set_current_line(286, ng0);

LAB38:    xsi_set_current_line(287, ng0);
    t19 = (t0 + 1368U);
    t20 = *((char **)t19);
    t19 = (t0 + 1528U);
    t30 = *((char **)t19);
    memset(t35, 0, 8);
    xsi_vlog_signed_divide(t35, 32, t20, 32, t30, 32);
    t19 = (t0 + 2248);
    xsi_vlogvar_wait_assign_value(t19, t35, 0, 0, 32, 0LL);
    xsi_set_current_line(288, ng0);
    t2 = (t0 + 1368U);
    t3 = *((char **)t2);
    t2 = (t0 + 1528U);
    t5 = *((char **)t2);
    memset(t34, 0, 8);
    xsi_vlog_signed_mod(t34, 32, t3, 32, t5, 32);
    t2 = (t0 + 2088);
    xsi_vlogvar_wait_assign_value(t2, t34, 0, 0, 32, 0LL);
    goto LAB37;

LAB41:    t12 = (t4 + 4);
    *((unsigned int *)t4) = 1;
    *((unsigned int *)t12) = 1;
    goto LAB42;

LAB43:    xsi_set_current_line(290, ng0);

LAB46:    xsi_set_current_line(291, ng0);
    t19 = (t0 + 1368U);
    t20 = *((char **)t19);
    t19 = (t0 + 1528U);
    t30 = *((char **)t19);
    memset(t35, 0, 8);
    xsi_vlog_unsigned_divide(t35, 32, t20, 32, t30, 32);
    t19 = (t0 + 2248);
    xsi_vlogvar_wait_assign_value(t19, t35, 0, 0, 32, 0LL);
    xsi_set_current_line(292, ng0);
    t2 = (t0 + 1368U);
    t3 = *((char **)t2);
    t2 = (t0 + 1528U);
    t5 = *((char **)t2);
    memset(t34, 0, 8);
    xsi_vlog_unsigned_mod(t34, 32, t3, 32, t5, 32);
    t2 = (t0 + 2088);
    xsi_vlogvar_wait_assign_value(t2, t34, 0, 0, 32, 0LL);
    goto LAB45;

LAB49:    t12 = (t4 + 4);
    *((unsigned int *)t4) = 1;
    *((unsigned int *)t12) = 1;
    goto LAB50;

LAB51:    xsi_set_current_line(294, ng0);

LAB54:    xsi_set_current_line(295, ng0);
    t19 = (t0 + 1368U);
    t20 = *((char **)t19);
    t19 = (t0 + 2088);
    xsi_vlogvar_wait_assign_value(t19, t20, 0, 0, 32, 0LL);
    xsi_set_current_line(296, ng0);
    t2 = (t0 + 2248);
    t3 = (t2 + 56U);
    t5 = *((char **)t3);
    t6 = (t0 + 2248);
    xsi_vlogvar_wait_assign_value(t6, t5, 0, 0, 32, 0LL);
    goto LAB53;

LAB57:    t12 = (t4 + 4);
    *((unsigned int *)t4) = 1;
    *((unsigned int *)t12) = 1;
    goto LAB58;

LAB59:    xsi_set_current_line(298, ng0);

LAB62:    xsi_set_current_line(299, ng0);
    t19 = (t0 + 2088);
    t20 = (t19 + 56U);
    t30 = *((char **)t20);
    t32 = (t0 + 2088);
    xsi_vlogvar_wait_assign_value(t32, t30, 0, 0, 32, 0LL);
    xsi_set_current_line(300, ng0);
    t2 = (t0 + 1368U);
    t3 = *((char **)t2);
    t2 = (t0 + 2248);
    xsi_vlogvar_wait_assign_value(t2, t3, 0, 0, 32, 0LL);
    goto LAB61;

}


extern void work_m_00000000000346521696_3164696072_init()
{
	static char *pe[] = {(void *)Always_274_0};
	xsi_register_didat("work_m_00000000000346521696_3164696072", "isim/tb_SingleCycle_isim_beh.exe.sim/work/m_00000000000346521696_3164696072.didat");
	xsi_register_executes(pe);
}
