/*
Smurf Combat
Copyright (C) 1993, 1994, 2019 Laurence Maar
laurencemaar@gmail.com
https://www.facebook.com/laurencemaar/
https://www.linkedin.com/in/laurencemaar/
*/

/*
This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

/***************************************************************************/
/*                                                                         */
/*   sss                       fff     ccc                 b               */
/*  s   s                     f   f   c   c                b               */
/*  s                         f       c                    b               */
/*   sss  mmm mmm  u   u r rr  fff    c      ooo  mmm mmm   bbb  aaa  ttt  */
/*      s m  m   m u   u rr   f       c     o   o m  m   m b   b a  a  t   */
/*  s   s m  m   m u  uu r    f       c   c o   o m  m   m b   b aaaa  t   */
/*   sss  m  m   m  uu u r    f        ccc   ooo  m  m   m  bbb  a  a  t   */
/*                                                                         */
/* SYSOP Maintenance Code: !-S-Y-S-O-P-!                            ARENA  */
/* REMOTE Maintenance Code: !-SIX-NINE-|                           MODULE  */
/*                                                                         */
/***************************************************************************/

#include "smurfext.h"





void arena(void){
  int arenalevel, erand,run=0,hit=0, enemyhp;
  char enemie[31],eweapon[31],earmor[31],*mac;int ews,aws;
  float gf,ef;

  roundsleft--;
  if(roundsleft<0){
    roundsleft=0;
    od_printf("\n\rOutta Turns!\n\n\r");
    return;}

//  stream=fopen("SMURF.LOG","a+");
//    fprintf(stream, "ARENA(%i):%s ... ",od_control.user_num,smurfname[thisuserno]);
//    fclose(stream);

  od_clr_scr();
//  if(random(5)==1)registerme();
  sprintf(mac,"%c",bbsinkey);
  arenalevel=atoi(mac);
  if(arenalevel==0)arenalevel=10;

  erand=random(10);
  ews=random(8)+1;
  aws=random(8)+1;

  if(arenalevel<2 && smurflevel[thisuserno]<4){
    ews=random(4)+1;
    aws=random(3)+1;
    }

  enemyhp=(random(arenalevel*4)+(8*arenalevel));
  strset(eweapon,0);strset(earmor,0);

    if(eweapno[arenalevel-1][erand]>99)
	sprintf(eweapon,"%s",enemieweap[eweapno[arenalevel-1][erand]-100]);else
	sprintf(eweapon,"%s",defweapon[eweapno[arenalevel-1][erand]]);
    if(earmrno[arenalevel-1][erand]>99)
	sprintf(earmor,"%s",enemiearmr[earmrno[arenalevel-1][erand]-100]);else
	sprintf(earmor,"%s",defarmor[earmrno[arenalevel-1][erand]]);

  sprintf(enemie,"%s",defenemie[arenalevel-1][erand]);
    od_set_colour(L_CYAN,D_BLACK);
    od_printf("A %s %s\n\r",enemie,defstartline[erand]);
    od_set_colour(L_GREEN,D_BLACK);
    od_printf("Y.Weapon: %s, %i Pts\n\rY.Defense: %s, %i Pts\n\r",smurfweap[thisuserno],(smurfweapno[thisuserno]+1)*5,smurfarmr[thisuserno],(smurfarmrno[thisuserno]+1)*4);
    od_printf("E.Weapon: %s, %i Pts\n\rE.Defense: %s, %i Pts\n\n\r",eweapon,(arenalevel-1)*10+ews,earmor,(arenalevel-1)*8+aws);

      do{
	od_set_colour(D_CYAN,D_BLACK);od_printf("He has %i points left.\n\r",enemyhp);
	od_set_colour(D_CYAN,D_BLACK);od_printf("You have %i points left.\n\r",smurfhp[thisuserno]);
	od_set_colour(L_YELLOW,D_BLACK);od_printf("(A)ttack (R)un (S)tats: ",enemie);
	   bbsinkey=od_get_key(TRUE);
	     od_set_colour(L_CYAN,D_BLACK);

	  switch(bbsinkey){
	  case 'A':case 'a':  od_set_colour(L_CYAN,D_BLACK);  od_printf("Attack!\n\r");hit=(random((smurfweapno[thisuserno]+1)*5))+1;hit=hit-random((arenalevel-1)*10+aws);
			    if(hit<0)hit=0;
			    enemyhp=(enemyhp-hit);
			    __hit(hit);
			      if(enemyhp>0){hit=(random((arenalevel-1)*10+ews))+1;hit=hit-random(smurfarmrno[thisuserno]*4);
				if(hit<0)hit=0;
				smurfhp[thisuserno]=(smurfhp[thisuserno]-hit);
				__ehit(hit,0);
			      }
			    /*if(enemyhp>0 && smurfhp[thisuserno]>0)od_clr_scr();else*/ nl();nl();break;
	  case 'R':case 'r':run=1;
			    od_printf("Run\n\n\rWimp!\n\n\r");
			    smurflose[thisuserno]++;
			    if(random(20)==1)deductmorale();
			    if(random(5)==1){deductettemorale();od_printf("Your smurfette is ashamed to know you...\n\r");}
			    nl();
			    break;
	  case 'S':case 's':od_set_colour(L_CYAN,D_BLACK);od_clr_scr();
	  deafult:nl();nl();break;
    od_printf("Enemie: %s [ArenaLevel: %i]\n\r",enemie,arenalevel);od_set_colour(L_GREEN,D_BLACK);
    od_printf("Y.Weapon: %s, %i Pts\n\rY.Defense: %s, %i Pts\n\r",smurfweap[thisuserno],(smurfweapno[thisuserno]+1)*5,smurfarmr[thisuserno],(smurfarmrno[thisuserno]+1)*4);
    od_printf("E.Weapon: %s, %i Pts\n\rE.Defense: %s, %i Pts\n\n\r",eweapon,(arenalevel-1)*10+ews,earmor,(arenalevel-1)*8+aws);break;
	  }
      }while(enemyhp>0 && smurfhp[thisuserno]>0 && run!=1);

if(smurfhp[thisuserno]<1){
  od_printf("\n\n\rLooks like we have a problem here...\n\n\r");
  smurfhp[thisuserno]=smurfhpm[thisuserno];
  fprintf(stream, "LOST!(%i):",od_control.user_num);
  fprintf(stream, "%-30s\n\r",smurfname[thisuserno]);
  fclose(stream);
  savegame();
  lastquote();
  od_exit(10,FALSE);
  }

if(enemyhp<1){
  gf=smurflevel[thisuserno]+1;
  gf*=arenalevel;
  gf*=(random(100));
  gf+=(69*smurflevel[thisuserno]);
  ef=smurflevel[thisuserno]+1;
  ef*=arenalevel;
  ef*=(random(100));
  ef+=(69*smurflevel[thisuserno]);
  od_printf("\n\n\rThe arena roars as you defeat the %s...\n\n\r",enemie);
  od_printf("You found %.0f gold and get %.0f experience!\n\n\r",gf,ef);
  smurfmoney[thisuserno]=(smurfmoney[thisuserno]+gf);
  smurfexper[thisuserno]=(smurfexper[thisuserno]+ef);
  fprintf(stream, "CHAM!(%i):",od_control.user_num);
  fprintf(stream, "%-30s\n\r",smurfname[thisuserno]);
  fclose(stream);
  checklevel();
  savegame();}
}

