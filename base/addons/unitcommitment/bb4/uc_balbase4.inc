* UC Translated to BB4 by Juan Gea Berm�dez 2018.

* Additional equations in model definition:

QUCVUCON
QUCVUCU
QUCVUCD
QUCSTARTQ
QUCMAXVGF


$ifi %MINFUELCONS%==yes QUCMINVGF

$ifi %MINSTARTUPTIME%==yes    QUCUT

$ifi %MINSHUTDOWNTIME%==yes    QUCDT

$ifi not %STEPWISERAMPING%==yes $goto STEPWISERAMPING_END
QUCRAMPU
QUCRAMPING_UP_BALANCE
QUCRAMPING_UP_RATE_CAPABILITY
QUCRAMPD
QUCRAMPING_DOWN_BALANCE
QUCRAMPING_DOWN_RATE_CAPABILITY
$label  STEPWISERAMPING_END