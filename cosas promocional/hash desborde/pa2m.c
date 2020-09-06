#include "pa2m.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct pa2m{
    int pruebas_totales;
    int pruebas_exitosas;
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
pa2m_t* pa2m_crear(){
    return calloc(1, sizeof(pa2m_t));
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void pa2m_avisar(char* aviso){
    printf(AMARILLO_F"%s"RESET_COLOR"\n", aviso);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void pa2m_asegurar(pa2m_t* probador, char* descripcion, bool cosas){
    if(!probador)
        return;

    if(cosas){
        probador->pruebas_exitosas++;
    }
    probador->pruebas_totales++;
    printf("Prueba: %s %s\n", descripcion, cosas? VERDE_F"EXITO"RESET_COLOR: ROJO_F"FALLA"RESET_COLOR);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void pa2m_mostrar_estadisticas(pa2m_t* probador){
    if(!probador)
        return;
    printf(CYAN_F"Pruebas exitosas: %i de %i"RESET_COLOR"\n", probador->pruebas_exitosas, probador->pruebas_totales);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void pa2m_destruir(pa2m_t* probador){
    free(probador);
}