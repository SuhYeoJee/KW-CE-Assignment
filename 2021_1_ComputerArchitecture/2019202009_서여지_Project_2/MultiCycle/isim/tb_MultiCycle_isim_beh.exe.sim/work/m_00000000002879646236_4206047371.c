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
static const char *ng0 = "C:/Users/gun07/Documents/ISE/MultiCycle/MultiCycle.v";
static unsigned int ng1[] = {0U, 0U};
static unsigned int ng2[] = {1U, 0U};
static unsigned int ng3[] = {65535U, 0U};



static void Always_97_0(char *t0)
{
    char t6[8];
    char t28[8];
    char t29[8];
    char t41[8];
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    char *t7;
    char *t8;
    unsigned int t9;
    unsigned int t10;
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
    char *t21;
    char *t22;
    unsigned int t23;
    unsigned int t24;
    unsigned int t25;
    unsigned int t26;
    unsigned int t27;
    char *t30;
    char *t31;
    char *t32;
    unsigned int t33;
    unsigned int t34;
    unsigned int t35;
    unsigned int t36;
    unsigned int t37;
    unsigned int t38;
    char *t39;
    char *t40;
    unsigned int t42;
    unsigned int t43;
    unsigned int t44;
    unsigned int t45;
    unsigned int t46;
    unsigned int t47;

LAB0:    t1 = (t0 + 2528U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(97, ng0);
    t2 = (t0 + 2848);
    *((int *)t2) = 1;
    t3 = (t0 + 2560);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(97, ng0);

LAB5:    xsi_set_current_line(97, ng0);
    t4 = (t0 + 1208U);
    t5 = *((char **)t4);
    t4 = ((char*)((ng1)));
    memset(t6, 0, 8);
    t7 = (t5 + 4);
    t8 = (t4 + 4);
    t9 = *((unsigned int *)t5);
    t10 = *((unsigned int *)t4);
    t11 = (t9 ^ t10);
    t12 = *((unsigned int *)t7);
    t13 = *((unsigned int *)t8);
    t14 = (t12 ^ t13);
    t15 = (t11 | t14);
    t16 = *((unsigned int *)t7);
    t17 = *((unsigned int *)t8);
    t18 = (t16 | t17);
    t19 = (~(t18));
    t20 = (t15 & t19);
    if (t20 != 0)
        goto LAB9;

LAB6:    if (t18 != 0)
        goto LAB8;

LAB7:    *((unsigned int *)t6) = 1;

LAB9:    t22 = (t6 + 4);
    t23 = *((unsigned int *)t22);
    t24 = (~(t23));
    t25 = *((unsigned int *)t6);
    t26 = (t25 & t24);
    t27 = (t26 != 0);
    if (t27 > 0)
        goto LAB10;

LAB11:    xsi_set_current_line(98, ng0);

LAB14:    xsi_set_current_line(98, ng0);
    t2 = (t0 + 1048U);
    t3 = *((char **)t2);
    memset(t6, 0, 8);
    t2 = (t6 + 4);
    t4 = (t3 + 4);
    t9 = *((unsigned int *)t3);
    t10 = (t9 >> 15);
    t11 = (t10 & 1);
    *((unsigned int *)t6) = t11;
    t12 = *((unsigned int *)t4);
    t13 = (t12 >> 15);
    t14 = (t13 & 1);
    *((unsigned int *)t2) = t14;
    t5 = ((char*)((ng2)));
    memset(t28, 0, 8);
    t7 = (t6 + 4);
    t8 = (t5 + 4);
    t15 = *((unsigned int *)t6);
    t16 = *((unsigned int *)t5);
    t17 = (t15 ^ t16);
    t18 = *((unsigned int *)t7);
    t19 = *((unsigned int *)t8);
    t20 = (t18 ^ t19);
    t23 = (t17 | t20);
    t24 = *((unsigned int *)t7);
    t25 = *((unsigned int *)t8);
    t26 = (t24 | t25);
    t27 = (~(t26));
    t33 = (t23 & t27);
    if (t33 != 0)
        goto LAB18;

LAB15:    if (t26 != 0)
        goto LAB17;

LAB16:    *((unsigned int *)t28) = 1;

LAB18:    t22 = (t28 + 4);
    t34 = *((unsigned int *)t22);
    t35 = (~(t34));
    t36 = *((unsigned int *)t28);
    t37 = (t36 & t35);
    t38 = (t37 != 0);
    if (t38 > 0)
        goto LAB19;

LAB20:    xsi_set_current_line(99, ng0);

LAB23:    xsi_set_current_line(99, ng0);
    t2 = (t0 + 1048U);
    t3 = *((char **)t2);
    memset(t28, 0, 8);
    t2 = (t28 + 4);
    t4 = (t3 + 4);
    t9 = *((unsigned int *)t3);
    t10 = (t9 >> 0);
    *((unsigned int *)t28) = t10;
    t11 = *((unsigned int *)t4);
    t12 = (t11 >> 0);
    *((unsigned int *)t2) = t12;
    t13 = *((unsigned int *)t28);
    *((unsigned int *)t28) = (t13 & 65535U);
    t14 = *((unsigned int *)t2);
    *((unsigned int *)t2) = (t14 & 65535U);
    t5 = ((char*)((ng1)));
    xsi_vlogtype_concat(t6, 32, 32, 2U, t5, 16, t28, 16);
    t7 = (t0 + 1608);
    xsi_vlogvar_assign_value(t7, t6, 0, 0, 32);

LAB21:
LAB12:    goto LAB2;

LAB8:    t21 = (t6 + 4);
    *((unsigned int *)t6) = 1;
    *((unsigned int *)t21) = 1;
    goto LAB9;

LAB10:    xsi_set_current_line(97, ng0);

LAB13:    xsi_set_current_line(97, ng0);
    t30 = (t0 + 1048U);
    t31 = *((char **)t30);
    memset(t29, 0, 8);
    t30 = (t29 + 4);
    t32 = (t31 + 4);
    t33 = *((unsigned int *)t31);
    t34 = (t33 >> 0);
    *((unsigned int *)t29) = t34;
    t35 = *((unsigned int *)t32);
    t36 = (t35 >> 0);
    *((unsigned int *)t30) = t36;
    t37 = *((unsigned int *)t29);
    *((unsigned int *)t29) = (t37 & 65535U);
    t38 = *((unsigned int *)t30);
    *((unsigned int *)t30) = (t38 & 65535U);
    t39 = ((char*)((ng1)));
    xsi_vlogtype_concat(t28, 32, 32, 2U, t39, 16, t29, 16);
    t40 = (t0 + 1608);
    xsi_vlogvar_assign_value(t40, t28, 0, 0, 32);
    goto LAB12;

LAB17:    t21 = (t28 + 4);
    *((unsigned int *)t28) = 1;
    *((unsigned int *)t21) = 1;
    goto LAB18;

LAB19:    xsi_set_current_line(98, ng0);

LAB22:    xsi_set_current_line(98, ng0);
    t30 = (t0 + 1048U);
    t31 = *((char **)t30);
    memset(t41, 0, 8);
    t30 = (t41 + 4);
    t32 = (t31 + 4);
    t42 = *((unsigned int *)t31);
    t43 = (t42 >> 0);
    *((unsigned int *)t41) = t43;
    t44 = *((unsigned int *)t32);
    t45 = (t44 >> 0);
    *((unsigned int *)t30) = t45;
    t46 = *((unsigned int *)t41);
    *((unsigned int *)t41) = (t46 & 65535U);
    t47 = *((unsigned int *)t30);
    *((unsigned int *)t30) = (t47 & 65535U);
    t39 = ((char*)((ng3)));
    xsi_vlogtype_concat(t29, 32, 32, 2U, t39, 16, t41, 16);
    t40 = (t0 + 1608);
    xsi_vlogvar_assign_value(t40, t29, 0, 0, 32);
    goto LAB21;

}


extern void work_m_00000000002879646236_4206047371_init()
{
	static char *pe[] = {(void *)Always_97_0};
	xsi_register_didat("work_m_00000000002879646236_4206047371", "isim/tb_MultiCycle_isim_beh.exe.sim/work/m_00000000002879646236_4206047371.didat");
	xsi_register_executes(pe);
}
