SETS
ISSSTTTMMM(SSS,TTT,MMM) 'relationship between season&hour and month'
IGR_TIME(GRDATASET,RRR,SSS,TTT)

IRESE(DEUSER) 'residential electricity consumption'
;


ISSSTTTMMM(S,T,MMM) = YES$(SSSTTTMMM(S,T) = MMM.val);


IGR_TIME(GRDATASET,IR,S,T) = YES$( SUM((C,MMM)$(CCCRRR(C,IR) and ISSSTTTMMM(S,T,MMM)), GRTIME_M(C,GRDATASET,MMM)) eq 1);
IGR_TIME('GRDTOU1',IR,S,T)$(NOT SUM(C$CCCRRR(C,IR), GRTIME_T(C,'GRDTOU1',T))) = NO;
IGR_TIME('GRDTOU2',IR,S,T)$(NOT SUM(C$CCCRRR(C,IR), GRTIME_T(C,'GRDTOU2',T))) = NO;
IGR_TIME('GRDTOU3',IR,S,T)$(NOT SUM(C$CCCRRR(C,IR), GRTIME_T(C,'GRDTOU3',T))) = NO;
IGR_TIME('GRDDCTOU',IR,S,T)$(NOT SUM(C$CCCRRR(C,IR), GRTIME_T(C,'GRDDCTOU',T))) = NO;
IGR_TIME('GRDDCY',IR,S,T)$(NOT SUM(C$CCCRRR(C,IR), GRTIME_T(C,'GRDDCY',T)) AND SUM((ITALIAS,C)$CCCRRR(C,IR), GRTIME_T(C,'GRDDCY',ITALIAS))) = NO;  

IRESE('RESE') = YES;
