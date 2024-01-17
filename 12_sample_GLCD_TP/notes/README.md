- [Volume](#volume)
	- [Implementazione](#implementazione)

# Volume

Il volume in questa applicazione viene implementato nella libreria `sound` che mette a disposizione le sue API attraverso il file `sound.h`, permette di usare due funzioni per poter leggere o settare il valore del volume corrente e la possibilità di fare il play di piccoli suoni, che al momento sono 4:
1. death
2. click
3. cuddles
4. death

## Implementazione

L'implementazione dei suoni viene fatta usando due periferiche: il DAC ed il TIMER. Per poter fare il play di usa nota si ha disposizione una tabella con i valori delle frequenze in Hz delle note.

La ripruzione di una nota consiste nel dare al DAC una serie di valori, che corrispondono a quelli di una sinusoide all'interno della frequenza della nota, per fare ciò viene calcolato il seguente intervallo, che corrisponde al perdiodo di tempo dopo il quale deve essere scatenate l'interruzione:

$$
T_{interrupt} = \frac{1s}{f_{nota} \cdot n} 
$$

Dove $n$ corrisponde al numero di valori del seno (che sono già precomputati in tabelle).

Il valore da assegnare al `match_register` è:
```c
// TIMER_CLK = 25MHz
// SIN_VAL = 45
int val = TIMER_CLK / (f_note * SIN_VAL);
```

Ad ogni interuupt che viene scatenato viene settato il prossimo valore del seno all'interno del DAC nel seguente modo:
```c
void song_call(void)
{
	if (sin_time >= SIN_VAL) {
		sin_time = 0;
	}

    // ...

	DAC_set_output(sin_wave[sound_volume][sin_time++]);
}
```
La variabile `sound_vaule` serve scegliere tra i 4 livelli di ampiezza della sinusoide.

Se si vuole riprodurre di una serie di note in sequenza si utilizza la struttura:
```c
typedef struct note_t {
    uint16_t note;
    uint16_t freq;
} note_t;
```
Dove:

- `note` contiene la frequenza della nota.
- `freq` contiene la durata della nota, i valori sono:
    - 0: la nota ha la stessa durata
    - 1: la nota ha la durata divisa per 2
    - 2: la nota ha la durate divisa per 4
    - ...

La durata base di una nota vale $0.5s$, per suonare note successive si utilizza un check e poi si cambia l'intervallo del `match_register` in uso:
```c
void song_call(void)
{
	// A full note "0" has to last 0.5 seconds
	if (curr_exec == (song[curr_note].note >> song[curr_note].freq) * SIN_VAL / 2)
	{
		curr_exec = 0; // numero di esecuzioni dell'interruzione
		curr_note++;
		
        // ...
		
		TIMER_match_reg(
			S_TIMER,
			S_MATCH,
			CONTROL_INTERRUPT | CONTROL_RESET,
			div(BASE_SIN_TIME, song[curr_note].note).quot,
			false
		);
	}

    // ...
}
```

Per usare queste funzioni vengono definite delle variabili globali che servono a gestire: quale canzone far sentire, il numero di note presenti, il volume ed valore del seno da dare in uscita:
```c
uint32_t sound_volume = 0;
uint32_t sin_time = 0;
uint32_t curr_note = 0;
uint32_t curr_exec = 0;
note_t *song = NULL;
uint32_t song_len = 0;
```