#pragma once
//Hardware scancodes https://www.win.tue.nl/~aeb/linux/kbd/scancodes-1.html
//Scancodes
#define esc_sc 0x01
#define enter_sc 0x1c
#define lctrl_sc 0x1d
#define lshift_sc 0x2a
#define space_sc 0x39

#define mbutton_sc 0x46


//cifre
#define c0_sc 0x0b
#define c1_sc 0x02
#define c2_sc 0x03
#define c3_sc 0x04
#define c4_sc 0x05
#define c5_sc 0x06
#define c6_sc 0x07
#define c7_sc 0x08
#define c8_sc 0x09
#define c9_sc 0x0a


//litere
#define a_sc 0x1e
#define b_sc 0x30
#define c_sc 0x2e
#define d_sc 0x20
#define e_sc 0x12
#define f_sc 0x21
#define g_sc 0x22
#define h_sc 0x23
#define i_sc 0x17
#define j_sc 0x24
#define k_sc 0x25
#define l_sc 0x26
#define m_sc 0x33
#define n_sc 0x31
#define o_sc 0x18
#define p_sc 0x19
#define q_sc 0x10
#define r_sc 0x13
#define s_sc 0x1f
#define t_sc 0x14
#define u_sc 0x16
#define w_sc 0x11
#define y_sc 0x15
#define z_sc 0x2c
#define v_sc 0x2f

//numpad
#define numpad1_sc 0x4f
#define numpad2_sc 0x50
#define numpad3_sc 0x51
#define numpad4_sc 0x4b
#define numpad5_sc 0x4c
#define numpad6_sc 0x4d
#define numpad7_sc 0x47
#define numpad8_sc 0x48

#define f1_sc 0x3b
#define f2_sc 0x3c
#define f3_sc 0x3d
#define f4_sc 0x3e


//Ascii Codes

#define w_key 0x57
#define a_key 0x41
#define s_key 0x53
#define d_key 0x44

#define space_key 0x20
#define enter_key 0x0D

#define f1_key 0x11
#define f2_key 0x12
#define f3_key 0x13
#define f4_key 0x14

#define c0_key 0x00
#define c1_key 0x01
#define c2_key 0x02
#define c3_key 0x03
#define c4_key 0x04
#define c5_key 0x05
#define c6_key 0x06
#define c7_key 0x07
#define c8_key 0x08
#define c9_key 0x09

#define lctrl_key 0x07



void pressKey(unsigned char sc_key, unsigned char key, int delay);