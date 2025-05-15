namespace Eclipse{
    class Autonomous_Paths{
    public:
        bool goal_rush = false;
        // Red side autons
        class Red{
            public:
                void solo_awp();
                void left_half_awp();
                void right_half_awp();
                void ring_side_rush();
                void goal_side_rush();
        };

        // Blue side autons
        class Blue{
            public:
                void solo_awp();
                void left_half_awp();
                void right_half_awp();
                void ring_side_rush();
                void goal_side_rush();
        };
        
        void skills();
        void test();
    };
}