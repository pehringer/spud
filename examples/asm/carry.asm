      ld MAX
      ad ONE
      jc CARRY
      ld FALSE
      st PUTC
      ja HALT
CARRY ld TRUE
      st PUTC
HALT  ja HALT


ZERO  0
ONE   1
MAX   65535
FALSE 48
TRUE  49
