#pragma once
#define IN_MAX_LEN_TEXT 1024*1024
#define IN_CODE_ENDL '\n'
#define IN_CODE_TABLE {\
  IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F,/*\n*/ '|', IN::F, IN::F, IN::F, IN::F, IN::F, \
  IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, \
 /* */ IN::T, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, \
 /*0*/ IN::T,/*1*/ IN::T, /*2*/IN::T, /*3*/IN::T, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, \
  IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F,/*N*/ IN::T, IN::F, \
  IN::F, IN::F, /*R*/IN::T, IN::F, IN::F, IN::F, IN::F, IN::F, /*X*/IN::I, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F,/*-*/ IN::T, \
  IN::F, /*a*/IN::T, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, /*k*/IN::T,/*l*/ IN::T, IN::F, /*n*/IN::T,/*o*/ IN::T, \
  IN::F, IN::F, /*r*/IN::T, /*s*/IN::T, /*t*/IN::T,/*u*/ IN::T, IN::F, IN::F, IN::F, /*y*/IN::T, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, \
                                                                                                                  \
  IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, \
  IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, \
  IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, \
  IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, \
  /*A*/'-', IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::T, IN::F, IN::F, IN::F, IN::F, /*H*/ IN::T, IN::F, IN::F, \
  /*P*/IN::T, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, \
  /*a*/IN::T, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F,/*ê*/ IN::T, /*ë*/IN::T, IN::F,/*í*/ IN::T, IN::F, IN::F, \
 /*ð*/ IN::T,/*c*/ IN::T,/*ò*/ IN::T, /*y*/IN::T, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, /*ü*/IN::T, IN::F, IN::F, /*ÿ*/IN::T \
    }

namespace In
{
    struct IN
    {
        enum { T = 1024, F = 2048, I = 4096 };
        int size;
        int lines;
        int ignor;
        unsigned char* text;
        int code[256] = IN_CODE_TABLE;
    };
    IN getin(wchar_t infile[]);
}