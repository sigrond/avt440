#ifndef AVT440DRIVER_H
#define AVT440DRIVER_H


class avt440driver
{
    public:
        /** Default constructor */
        avt440driver();
        /** Default destructor */
        ~avt440driver();

        /** \brief pobranie statusu
         *
         * \return int
         *
         */
        int getStatus();

        /** \brief ustawienie wyjœcia A
         *
         * \param char unsigned
         * \return void
         *
         */
        void setOutputA(unsigned char);

        /** \brief ustawienie wyjœcia B
         *
         * \param char unsigned
         * \return void
         *
         */
        void setOutputB(unsigned char);

        /** \brief pobranie wejœcia A
         *
         * \return unsigned char
         *
         */
        unsigned char getInputA();

        /** \brief pobranie wejœcia B
         *
         * \return unsigned char
         *
         */
        unsigned char getInputB();

        /** \brief pobranie rejestru statusu
         *
         * \return unsigned char
         *
         */
        unsigned char getStatusRegister();

        /** \brief sekwencja przepisujaca bez przeniesienia danych przez port
         *
         * \return void
         *
         */
        void setInputAtoOutputA();

        /** \brief sekwencja przepisujaca bez przeniesienia danych przez port
         *
         * \return void
         *
         */
        void setInputBtoOutputB();

        /** \brief otwarcie wejścia A
         *
         * \return void
         *
         */
        void openInputA();

        /** \brief otwarcie wejścia B
         *
         * \return void
         *
         */
        void openInputB();

        /** \brief zamkniecie wejsc
         *
         * \return void
         *
         */
        void closeInput();

        /** \brief pobranie otwartego wejscia
         *
         * \return unsigned char
         *
         */
        unsigned char getInput();

        /** \brief ustawienie bitów rejestru kontroli
         *
         * \param char unsigned
         * \return void
         *
         */
        void setControll(unsigned char);

        /** \brief specjalne pobranie wartości przez rejestr kontroli
         *
         * \return unsigned char
         *
         */
        unsigned char getControllFromDevice();

        /** \brief zwykłe pobranie rejestru kontroli
         *
         * \return unsigned char
         *
         */
        unsigned char getControll();


    protected:

    private:
        int status;
        unsigned char InA;
        unsigned char InB;
        unsigned char OutA;
        unsigned char OutB;
        unsigned char ctl;/**< control register */
};

#endif // AVT440DRIVER_H
