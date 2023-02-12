; Print "Hello World!"

DEFINE out_reg 1048577

hello:
  LOAD_I 'H'
  SWAP
  SAVE_A out_reg

  LOAD_I 'e'
  SWAP
  SAVE_A out_reg

  LOAD_I 'l'
  SWAP
  SAVE_A out_reg ; 1st 'l'
  SAVE_A out_reg ; 2nd 'l'

  LOAD_I 'o'
  SWAP
  SAVE_A out_reg

  LOAD_I ' '
  SWAP
  SAVE_A out_reg

world:
  LOAD_I 'W'
  SWAP
  SAVE_A out_reg

  LOAD_I 'o'
  SWAP
  SAVE_A out_reg

  LOAD_I 'r'
  SWAP
  SAVE_A out_reg

  LOAD_I 'l'
  SWAP
  SAVE_A out_reg

  LOAD_I 'd'
  SWAP
  SAVE_A out_reg

  LOAD_I '!'
  SWAP
  SAVE_A out_reg

  LOAD_I '\n'
  SWAP
  SAVE_A out_reg

HALT
