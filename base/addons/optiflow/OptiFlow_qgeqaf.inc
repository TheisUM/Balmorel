+SUM((IS3,T),VFLOWBUFFER(IA,'StrawElecHeatBuffer','STRAW_ELEC_HEAT',IS3,T)$((SUM(IPROCFROM$IFLOWFROMTOPROC_Y(IA,IPROCFROM,'StrawElecHeatBuffer','STRAW_ELEC_HEAT'),1)) AND IGEQF_Y(IA,'STRAW')))