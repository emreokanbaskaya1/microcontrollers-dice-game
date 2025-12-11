#include <16F877A.h>
#fuses XT, NOWDT, NOPROTECT, BROWNOUT, NOLVP, NOPUT, NOWRT, NODEBUG, NOCPD
#use delay(clock=4M)
#include <lcd420.c>

// LCD Pin Tanýmlarý
#define LCD_RS_PIN PIN_B1
#define LCD_RW_PIN PIN_B2
#define LCD_E_PIN  PIN_B0
#define LCD_D4_PIN PIN_B4
#define LCD_D5_PIN PIN_B5
#define LCD_D6_PIN PIN_B6
#define LCD_D7_PIN PIN_B7

// Global Deðiþkenler
int oyuncu1_zarlar[3] = {0}, oyuncu2_zarlar[3] = {0};
int oyuncu1_toplam = 0, oyuncu2_toplam = 0;
int zar_sayisi = 0;

// Timer0 ile Rastgele Zar Atýþý (1-6)
int zar_atisi() {
    int timer_value = get_timer0();
    set_timer0(timer_value + 11);  // Rastgeleliði artýrmak için
    return (timer_value % 6) + 1;
}

// LED Efekti (Hýzlandýrýldý)
void led_efekti() {
    for (int j = 0; j < 8; j++) {
        output_high(PIN_D0 + j);
        delay_ms(30);  // LED bekleme süresi azaltýldý
        output_low(PIN_D0 + j);
    }
}

// Hoþgeldiniz Yazýsýný Kaydýrma
void hosgeldiniz_mesaji() {
    for (int pos = 17; pos > 0; pos--) {
        lcd_putc("\f");
        lcd_gotoxy(pos, 1);
        printf(lcd_putc, "Hosgeldiniz!");
        delay_ms(30);  // Daha hýzlý kaydýrma
    }
}

// Zar Sonuçlarýný Güncelle
void guncelle_lcd() {
    lcd_putc("\f");
    lcd_gotoxy(1, 1);
    printf(lcd_putc, "P1: %d+%d+%d", oyuncu1_zarlar[0], oyuncu1_zarlar[1], oyuncu1_zarlar[2]);
    lcd_gotoxy(1, 2);
    printf(lcd_putc, "P2: %d+%d+%d", oyuncu2_zarlar[0], oyuncu2_zarlar[1], oyuncu2_zarlar[2]);
}

// Kazananý Göster
void kazanan_mesaji() {
    lcd_putc("\f");
    lcd_gotoxy(1, 1);
    printf(lcd_putc, "P1: %d   P2: %d", oyuncu1_toplam, oyuncu2_toplam);
    delay_ms(1000);

    lcd_putc("\f");
    lcd_gotoxy(1, 1);
    if (oyuncu1_toplam > oyuncu2_toplam) {
        printf(lcd_putc, "P1 Kazandi!");
    } else if (oyuncu2_toplam > oyuncu1_toplam) {
        printf(lcd_putc, "P2 Kazandi!");
    } else {
        printf(lcd_putc, "Berabere!");
    }
    delay_ms(1500);
}

// Oyunu Sýfýrla
void reset_oyun() {
    zar_sayisi = 0;
    oyuncu1_toplam = 0;
    oyuncu2_toplam = 0;
    for (int j = 0; j < 3; j++) {
        oyuncu1_zarlar[j] = 0;
        oyuncu2_zarlar[j] = 0;
    }
}

void main() {
    lcd_init();
    setup_timer_0(RTCC_INTERNAL | RTCC_DIV_256);
    set_tris_c(0x03);  // RC0 ve RC1 giriþ
    set_tris_d(0x00);  // RD çýkýþ (LED için)
    set_tris_b(0x00);  // RB çýkýþ (LCD için)

    while (TRUE) {
        // Çalýþtýr butonu için döngü
        lcd_putc("\f");
        lcd_gotoxy(1, 1);
        printf(lcd_putc, "Lutfen Calistir");
        lcd_gotoxy(1, 2);
        printf(lcd_putc, "Butonuna Basin!");
        while (!input(PIN_C0));
        delay_ms(100);

        // Hoþgeldiniz mesajý ve baþlangýç talimatý
        hosgeldiniz_mesaji();
        lcd_putc("\f");
        lcd_gotoxy(1, 1);
        printf(lcd_putc, "Start'a Basin!");
        reset_oyun();

        // Zar atýþ döngüsü
        while (zar_sayisi < 3) {
            // P1 atýþý
            lcd_putc("\f");
            lcd_gotoxy(1, 1);
            printf(lcd_putc, "P1 atis yapacak");
            while (!input(PIN_A0));
            delay_ms(100);
            oyuncu1_zarlar[zar_sayisi] = zar_atisi();
            oyuncu1_toplam += oyuncu1_zarlar[zar_sayisi];
            guncelle_lcd();
            led_efekti();

            // P2 atýþý
            lcd_putc("\f");
            lcd_gotoxy(1, 1);
            printf(lcd_putc, "P2 atis yapacak");
            while (!input(PIN_A0));
            delay_ms(100);
            oyuncu2_zarlar[zar_sayisi] = zar_atisi();
            oyuncu2_toplam += oyuncu2_zarlar[zar_sayisi];
            guncelle_lcd();
            led_efekti();

            zar_sayisi++;
        }

        // Kazananý göster
        kazanan_mesaji();

        // Reset butonu bekleme
        lcd_putc("\f");
        lcd_gotoxy(1, 1);
        printf(lcd_putc, "Reset icin");
        lcd_gotoxy(1, 2);
        printf(lcd_putc, "Butona Basin!");
        while (!input(PIN_C1));
        delay_ms(100);
    }
}

