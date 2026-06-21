// Al ajustar la hora el reloj queda en hora y es válida
// Después de n ciclos de reloj la hora avanza un segundo, diez
// y un día completo. Fijar la hora de la alarma y consultarla.
// La alarma, deshabilitarla y avanzar el reloj para que no suene
//
// Probar que el create no devuelve algo nulo
// Probar con una hora inálida
// Decidir que sucede con el reloj desconfigurado y el avance de la hora

#include "unity.h"
#include "reloj.h"

#ifndef TICKS_PER_SECOND
#define TICKS_PER_SECOND 3
#endif

#ifndef ONE_SECOND
#define ONE_SECOND TICKS_PER_SECOND
#endif

#ifndef TEN_SECONDS
#define TEN_SECONDS 10 * ONE_SECOND
#endif

static const hora_t DEFAULT_TIME = {0, 0, 0, 0, 0, 0};
static const hora_t TEST_TIME = {1, 2, 3, 4, 5, 6};

void SimulateClockTicks(clock_t clock, uint32_t ticks) {
    for (int i = 0; i < ticks; i++) {
        RelojNewTick(clock);
    }
}

// Al iniciar el reloj está en 00:00 y con una hora invalida.
void test_reloj_inicia_invalido(void) {
    clock_t reloj;
    hora_t hora_actual = {1, 2, 3, 4, 5, 6};

    reloj = RelojCreate(TICKS_PER_SECOND, NULL);

    // La función devuelve TRUE porque la hora es válida
    TEST_ASSERT_FALSE(RelojGetCurrentTime(reloj, hora_actual));

    // TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, actual, size);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(DEFAULT_TIME, hora_actual, 6);
}

// Al ajustar la hora del reloj queda en hora y es válida
void test_ajuste_de_hora(void) {
    clock_t reloj;
    hora_t hora_actual = {1, 2, 3, 4, 5, 6};
    // hora_t nueva_hora = {1, 5, 4, 3, 2, 1};
    hora_t nueva_hora = {1, 2, 3, 4, 5, 6};

    reloj = RelojCreate(TICKS_PER_SECOND, NULL);

    TEST_ASSERT_TRUE(RelojSetupCurrentTime(reloj, TEST_TIME));

    // La función devuelve TRUE porque la hora es válida
    TEST_ASSERT_TRUE(RelojGetCurrentTime(reloj, hora_actual));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(TEST_TIME, hora_actual, 6);
}

void test_avanza_un_segundo(void) {
    clock_t reloj;
    hora_t hora_actual;
    static const hora_t EXPECTED_TIME_1 = {1, 2, 3, 4, 5, 7};

    reloj = RelojCreate(TICKS_PER_SECOND, NULL);
    (void)RelojSetupCurrentTime(reloj, TEST_TIME);
    SimulateClockTicks(reloj, ONE_SECOND);
    RelojGetCurrentTime(reloj, hora_actual);

    TEST_ASSERT_TRUE(RelojGetCurrentTime(reloj, hora_actual));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(EXPECTED_TIME_1, hora_actual, 6);
}

void test_avanza_diez_segundos(void) {
    clock_t reloj;
    hora_t hora_actual;
    static const hora_t EXPECTED_TIME_2 = {1, 2, 3, 5, 0, 6};

    reloj = RelojCreate(TICKS_PER_SECOND, NULL);
    (void)RelojSetupCurrentTime(reloj, TEST_TIME);
    SimulateClockTicks(reloj, TEN_SECONDS);
    RelojGetCurrentTime(reloj, hora_actual);

    TEST_ASSERT_TRUE(RelojGetCurrentTime(reloj, hora_actual));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(EXPECTED_TIME_2, hora_actual, 6);
}

// void test_alarma_funciona(void) {
//     clock_t reloj;
//     hora_t alarma = {7, 7, 7, 7, 7, 7};
//     bool es_valida;

//     reloj = RelojCreate(1, NULL);
//     es_valida = RelojGetAlarm(reloj, alarma);

//     TEST_ASSERT_FALSE(es_valida);

//     // TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, actual, size);
//     TEST_ASSERT_EQUAL_UINT8_ARRAY(((hora_t){7, 7, 7, 7, 7, 7}), alarma, 6);
// };

/*

*/