/**********************************************
 * Title: Generating an ASCII table
 * Author: Osami Yamamoto
 * Date: Sun Apr  9 08:08:48 JST 2017
 **********************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tab{
  char meaning[6];
} tab;

static tab *make_table();
static void output(tab *tab);

static tab *make_table(){
  tab *table = (tab *)malloc(sizeof(tab) * 128);
  char *nums[] = {
    "NUL", "SOH", "STX", "ETX", "EOX", "ENQ", "ACK",
    "BEL", "BS", "HT", "LF", "VT", "FF", "CR", "SO",
    "SI", "DLE", "DC1", "DC2", "DC3", "DC4", "NAK",
    "SYN", "ETB", "CAN", "EM", "SUB", "ESC", "FS",
    "GS", "RS", "US", "SPACE", "DEL"};
  int i;
  for (i = 0; i < 128; i++){
    if (i <= 32) strcpy(table[i].meaning, nums[i]);
    else if (i == 127) strcpy(table[i].meaning, nums[33]);
    else{
      table[i].meaning[0] = (char)i;
      table[i].meaning[1] = '\0';
    }
  }
  return table;
} /* make_table */

static void output(tab *tab){
  enum {m = 4};
  int i, j, k;
  for (i = 0; i < 128 / m; i++){
    for (j = 0; j < m; j++){
      k = j * (128 / m) + i;
      printf("%03d %02x : %-6s", k, k, tab[k].meaning);
    }
    putchar('\n');
  }
} /* output */

int main(){
  tab *table = make_table();
  output(table);
  free(table);
  return 0;
} /* main */

/****
000 00 : NUL   032 20 : SPACE 064 40 : @     096 60 : `     
001 01 : SOH   033 21 : !     065 41 : A     097 61 : a     
002 02 : STX   034 22 : "     066 42 : B     098 62 : b     
003 03 : ETX   035 23 : #     067 43 : C     099 63 : c     
004 04 : EOX   036 24 : $     068 44 : D     100 64 : d     
005 05 : ENQ   037 25 : %     069 45 : E     101 65 : e     
006 06 : ACK   038 26 : &     070 46 : F     102 66 : f     
007 07 : BEL   039 27 : '     071 47 : G     103 67 : g     
008 08 : BS    040 28 : (     072 48 : H     104 68 : h     
009 09 : HT    041 29 : )     073 49 : I     105 69 : i     
010 0a : LF    042 2a : *     074 4a : J     106 6a : j     
011 0b : VT    043 2b : +     075 4b : K     107 6b : k     
012 0c : FF    044 2c : ,     076 4c : L     108 6c : l     
013 0d : CR    045 2d : -     077 4d : M     109 6d : m     
014 0e : SO    046 2e : .     078 4e : N     110 6e : n     
015 0f : SI    047 2f : /     079 4f : O     111 6f : o     
016 10 : DLE   048 30 : 0     080 50 : P     112 70 : p     
017 11 : DC1   049 31 : 1     081 51 : Q     113 71 : q     
018 12 : DC2   050 32 : 2     082 52 : R     114 72 : r     
019 13 : DC3   051 33 : 3     083 53 : S     115 73 : s     
020 14 : DC4   052 34 : 4     084 54 : T     116 74 : t     
021 15 : NAK   053 35 : 5     085 55 : U     117 75 : u     
022 16 : SYN   054 36 : 6     086 56 : V     118 76 : v     
023 17 : ETB   055 37 : 7     087 57 : W     119 77 : w     
024 18 : CAN   056 38 : 8     088 58 : X     120 78 : x     
025 19 : EM    057 39 : 9     089 59 : Y     121 79 : y     
026 1a : SUB   058 3a : :     090 5a : Z     122 7a : z     
027 1b : ESC   059 3b : ;     091 5b : [     123 7b : {     
028 1c : FS    060 3c : <     092 5c : \     124 7c : |     
029 1d : GS    061 3d : =     093 5d : ]     125 7d : }     
030 1e : RS    062 3e : >     094 5e : ^     126 7e : ~     
031 1f : US    063 3f : ?     095 5f : _     127 7f : DEL   
****/
