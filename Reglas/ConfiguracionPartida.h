//
// Created by sofia on 15/02/2026.
//

#ifndef JUEGOUNO_CONFIGURACIONPARTIDA_H
#define JUEGOUNO_CONFIGURACIONPARTIDA_H

enum TipoRobo {
    ROBO_UNA_Y_PASA,
    ROBO_HASTA_PODER_JUGAR
};

class ConfiguracionPartida {
public:
    bool permitirAcumulacion;
    bool permitirRetoMasCuatro;
    TipoRobo tipoRobo;
    bool permitirGritoUno;
    bool permitirGanarConNegra;

    bool activarUnoFlip;

    ConfiguracionPartida() {
        permitirAcumulacion = false;
        permitirRetoMasCuatro = false;
        tipoRobo = ROBO_UNA_Y_PASA;
        permitirGritoUno = false;
        permitirGanarConNegra = true;
        activarUnoFlip = false;
    }
};


#endif //JUEGOUNO_CONFIGURACIONPARTIDA_H