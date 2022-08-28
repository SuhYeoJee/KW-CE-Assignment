import java_cup.runtime.*;

%%

%class Scanner
%cup

%{
// ����� ���� �ڵ�
  private Symbol symbol(int type) {
    return new Symbol(type, yyline+1, yycolumn+1);
  }

  private Symbol symbol(int type, Object value) {
    return new Symbol(type, yyline+1, yycolumn+1, value);
  }

%}

//��ū ����
NUMBER = [0-9]+
IDENT = [A-Za-z][A-Za-z0-9]*

SEMICOLON = ";"
ASSIGN = "="
PLUS = "+"
MINUS = "-"
MULT = "*"
DIV = "/"
LPAREN = "("
RPAREN = ")"

%%
//�ν����� �� ����
<YYINITIAL> {
  {NUMBER}  { return symbol(sym.NUMBER, Integer.valueOf(yytext())); }
  {IDENT}   { return symbol(sym.IDENT, String.valueOf(yytext())); }

  ";"       { return symbol(sym.SEMICOLON); }
  "="       { return symbol(sym.ASSIGN); }
  "+"       { return symbol(sym.PLUS); }
  "-"       { return symbol(sym.MINUS); }
  "*"       { return symbol(sym.MULT); }
  "/"       { return symbol(sym.DIV); }
  "("       { return symbol(sym.LPAREN); }
  ")"       { return symbol(sym.RPAREN); }
}