
*Initializing the set IFPROC and IFFLOW if OPTIFLOW is enabled and the bridge of biomass usage between models, TMAD
$ifi not %baloptfuelbridge%==yes $goto nofuelbridge

SET IFFLOW(FFF,FLOW)	"Fuel in Balmorel that corresponds to a flow in OptiFlow";
IFFLOW(FFF,FLOW)=0;

IFFLOW('STRAW','STRAW_GEN_FLOW')=YES;
IFFLOW('WOODCHIPS','WOOD_GEN_FLOW')=YES;
*IFFLOW('BIOGAS','CO2_FLOW')=YES;

SET IFPROC(FFF,PROC)	"Fuel in Balmorel that corresponds to a flow in OptiFlow";
IFPROC(FFF,PROC)=0;

IFPROC('STRAW','Straw_Source')=YES;
IFPROC('WOODCHIPS','Wood_Source')=YES;
*IFPROC('BIOGAS','CO2_Source_Biogas')=YES;

$label nofuelbridge

*Initializing the set IFPROC and IFFLOW if OPTIFLOW is enabled and the bridge of biogas between models, TMAD
$ifi not %baloptgasbridge%==yes $goto nogasbridge
IFFLOW('BIOGAS','GASFLOW_GJ')=YES;
IFPROC('BIOGAS','BiogasBuffer')=YES;

$label nogasbridge

*Initializing CO2 sources
*$ifi not %baloptCCU%==yes $goto noCCUopti
SET ICO2(PROCSOURCE,FLOW)		"Set of CO2 source and flows";
ICO2(PROCSOURCE,FLOW)=0;
ICO2('CO2_Source_Biogen','CO2_FLOW') = YES;
ICO2('CO2_Source_Fossil','CO2_FLOW') = YES;

$label noCCUopti

$label endoffile