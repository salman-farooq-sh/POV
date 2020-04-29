const int LED_PIN[] = { 19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2 };
const uint32_t current_num_of_sectors = 240;

uint32_t current_time_period = 118000;

bool is_even( int n ) {
    return (n%2 == 0);
}

void delay_micro( uint32_t delay_micro ) {
    uint32_t delay_milli = delay_micro / 1000;
    delay_micro %= 1000;
    delay(delay_milli);
    delayMicroseconds(delay_micro);
}

void all_led_off() {
  for( int i = 0; i < 18; ++i ) {
      digitalWrite(LED_PIN[i], LOW);
  }
}

// takes a time of one rotation_time_period to execute:
void display_calibration_frame() {
    for ( int j = 1; j < 18; j += 2 ) { digitalWrite(LED_PIN[j], HIGH); }
    
    delay_micro( current_time_period / current_num_of_sectors );
    
    for ( int j = 1; j < 18; j += 2 ) { digitalWrite(LED_PIN[j], LOW); }
    for ( int j = 0; j < 18; j += 2 ) { digitalWrite(LED_PIN[j], HIGH); }
    
    delay_micro( current_time_period / current_num_of_sectors );
    
    for ( int j = 0; j < 18; j += 2 ) { digitalWrite(LED_PIN[j], LOW); }
    
    delay_micro( (current_num_of_sectors - 2) * (current_time_period / current_num_of_sectors) );
}

char last_column[18] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
void display_column( char current_column[18] ) {
    for( int led_no = 0; led_no < 18; ++led_no ) {
        if( is_even(led_no) ) {
            digitalWrite( LED_PIN[led_no], current_column[led_no] == '1' ? HIGH : LOW );
        } else {
            digitalWrite( LED_PIN[led_no], last_column[led_no] == '1' ? HIGH : LOW );
        }
    }

    for( int i = 0; i < 18; ++i ) {
        last_column[i] = current_column[i];
    }

    delay_micro( current_time_period / current_num_of_sectors );
}

// extracts the the specified 'column_number' (based on zero indexing) from 'frame' into 'column'
void extract_column(const unsigned char frame[135], int column_no, char column[18]) {
    int bit_index  = column_no * 18; // based on zero_indexing
    int byte_index = bit_index / 8;  // based on zero_indexing
    int offset     = bit_index % 8;  // based on zero_indexing

    for(int i = 0; i < 18; ++i) {
        unsigned char one = 1;
        unsigned int shift = (7 - offset);
        unsigned char mask = one << shift;
        column[i] = ( (frame[byte_index] & mask) == 0 ? 0 : 1) + '0';

        offset++;

        if(offset == 8) {
            byte_index++;
            offset = 0;
        }
    }
}


// hardcoded demo frames:
const unsigned char frame_no1[135] = { 0,0,0,0,0,0,0,0,0,12,0,3,0,1,255,0,120,32,30,8,7,130,1,192,64,112,16,28,4,2,112,128,156,32,37,0,9,73,2,82,64,156,80,39,20,8,5,2,1,64,128,80,32,84,8,5,2,1,64,128,80,39,20,9,193,2,82,64,148,144,37,0,9,194,6,112,129,192,64,112,16,30,12,7,130,1,224,128,127,192,12,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
const unsigned char frame_no2[135] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,28,0,15,128,2,48,1,4,0,65,128,34,32,8,136,4,114,1,28,128,66,32,16,152,4,4,1,3,0,64,128,16,32,4,8,31,2,7,192,128,16,32,4,8,1,2,0,64,192,16,144,4,38,1,20,128,69,32,16,136,2,34,0,128,128,16,96,4,16,0,140,0,62,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
const unsigned char frame_no3[135] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,112,128,62,32,15,152,3,226,3,253,128,255,96,56,232,14,186,3,142,128,227,160,56,232,31,250,7,254,129,255,224,127,248,62,62,23,175,137,227,224,120,232,62,58,23,254,137,255,160,127,232,31,250,7,254,128,255,160,63,200,15,246,3,252,128,62,96,15,152,1,192,0,112,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
const unsigned char frame_no4[135] = { 0,0,0,0,0,0,0,0,0,0,0,1,254,0,127,128,31,224,24,252,6,63,1,143,192,225,220,56,119,14,29,199,0,73,192,18,112,4,153,226,22,120,133,158,33,143,203,99,242,216,252,182,63,33,143,200,121,226,30,120,135,158,45,240,11,124,2,223,0,133,231,33,121,196,158,113,39,191,73,239,210,123,247,14,253,195,191,112,99,16,24,196,6,49,0,127,128,31,224,7,248,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
const unsigned char frame_no5[135] = { 0,192,0,48,0,255,192,63,240,127,255,255,255,255,0,63,192,15,0,0,0,0,0,0,0,0,0,0,0,14,0,3,128,1,16,0,68,0,17,0,3,128,0,224,0,0,6,0,0,192,0,48,0,6,0,1,128,0,48,0,15,224,131,248,32,193,8,48,66,12,16,131,4,32,192,240,48,60,12,0,6,0,1,128,0,192,0,48,0,24,0,0,0,0,3,128,0,224,0,68,0,17,0,4,64,0,224,0,56,0,0,0,0,0,0,0,0,240,3,252,0,255,255,253,255,255,15,252,3,255,0,12,0,3,0 };
//const unsigned char frame_no6[135] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,16,0,8,64,4,32,5,16,2,248,0,81,0,2,32,1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
//const unsigned char frame_no7[135]; // unused
void display_frame( char frame[135] ) {
    char current_column[18];
    for( int i = 0; i < 60; ++i ) {
        extract_column( frame, i, current_column );
        display_column( current_column );
    }

    delay_micro( 3 * 60 * (current_time_period / current_num_of_sectors) );

    all_led_off();
}


const unsigned char dino_animation[2][135] = {
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,240,0,28,0,7,0,0,192,0,56,0,14,0,1,128,0,112,0,28,0,7,0,3,252,0,254,0,63,0,31,192,7,224,1,240,0,124,0,31,0,15,192,3,248,15,254,3,255,192,255,248,127,240,31,248,4,254,1,63,0,79,192,31,64,7,208,1,244,0,125,0,31,64,7,216,1,240,0,120,0,30,0,3,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,240,0,28,0,7,0,0,192,0,56,0,14,0,1,128,0,112,0,28,0,7,0,3,248,0,252,0,62,0,31,128,7,192,1,240,0,124,0,31,0,15,224,3,252,15,255,3,255,224,255,252,127,240,31,248,4,254,1,63,0,79,192,31,64,7,208,1,244,0,125,0,31,64,7,216,1,240,0,120,0,30,0,3,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }
};
void display_dino_animation() {
    const uint32_t delay_between_animation_frames = 300; // in milliseconds
    
    uint32_t current_time = millis();
    while( millis() < current_time + delay_between_animation_frames ) {
        display_frame( dino_animation[0] );
    }

    current_time = millis();
    while( millis() < current_time + delay_between_animation_frames ) {
        display_frame( dino_animation[1] );
    }
}

const unsigned char music_visualizer_animation[4][135] = {
    { 0,0,64,0,48,0,28,0,1,0,0,192,3,240,0,12,0,127,0,7,192,0,16,0,12,0,3,0,3,192,0,16,0,12,0,3,0,0,192,255,240,31,252,0,7,0,31,192,0,16,0,4,0,1,1,255,192,0,16,0,4,0,7,0,7,207,255,241,255,252,15,255,0,0,64,0,16,0,12,0,63,0,7,192,0,16,0,4,0,1,0,15,192,15,243,255,252,7,255,0,3,192,0,16,0,4,0,7,0,3,192,0,112,1,252,1,255,0,255,192,7,240,0,28,0,1,0,0,64,1,240,0,52,0,3 },
    { 0,1,192,0,240,0,124,0,7,0,3,192,15,240,0,60,0,127,0,127,192,0,48,0,124,0,7,0,31,192,0,48,0,4,0,63,0,3,192,255,240,15,252,0,15,0,63,192,0,112,0,252,0,3,31,255,195,255,240,0,4,0,7,0,127,223,255,240,127,252,0,63,0,1,192,3,240,0,12,0,255,0,255,192,0,240,0,4,0,1,0,15,192,15,243,255,252,7,255,0,31,192,0,16,0,4,0,7,0,15,192,0,240,15,252,63,255,1,255,192,0,240,1,252,0,15,0,0,192,3,240,0,28,0,7 },
    { 0,15,192,15,243,255,252,7,255,0,31,192,0,16,0,4,0,7,0,15,192,0,240,15,252,63,255,1,255,192,0,240,1,252,0,15,0,0,192,3,240,0,28,0,7,127,255,192,0,16,0,4,0,1,1,255,192,0,16,0,4,0,7,0,7,207,255,241,255,252,15,255,0,0,64,0,16,0,12,0,63,0,7,192,0,16,0,4,0,1,0,1,192,0,240,0,124,0,7,0,3,192,15,240,0,60,0,127,0,127,192,0,48,0,124,0,7,0,31,192,0,48,0,4,0,63,0,3,192,255,240,15,252,0,15 },
    { 0,15,192,15,243,255,252,7,255,0,31,192,0,16,0,4,0,7,0,15,192,0,240,15,252,63,255,1,255,192,0,240,1,252,0,15,0,0,192,3,240,63,252,15,255,255,255,192,255,240,0,124,15,255,3,255,192,0,16,0,4,0,7,0,7,207,255,241,255,252,15,255,0,0,64,0,16,0,12,1,255,0,7,192,0,16,0,4,0,1,0,1,192,0,241,255,252,0,7,0,3,192,15,240,7,252,3,255,0,127,192,0,48,0,124,0,7,0,31,192,0,48,0,4,0,63,0,3,192,255,240,15,252,0,15 }
};
void display_music_visualizer() {
    const uint32_t delay_between_animation_frames = 170; // in milliseconds
    
    uint32_t current_time = millis();
    while( millis() < current_time + delay_between_animation_frames ) {
        display_frame( music_visualizer_animation[0] );
    }

    current_time = millis();
    while( millis() < current_time + delay_between_animation_frames ) {
        display_frame( music_visualizer_animation[1] );
    }

    current_time = millis();
    while( millis() < current_time + delay_between_animation_frames ) {
        display_frame( music_visualizer_animation[2] );
    }

    current_time = millis();
    while( millis() < current_time + delay_between_animation_frames ) {
        display_frame( music_visualizer_animation[3] );
    }
}

//const unsigned char ECG_frame[135] = { 0,128,0,32,0,8,0,2,0,0,128,0,32,0,24,0,12,0,6,0,3,0,0,192,0,24,0,3,0,0,96,0,12,0,1,128,0,96,0,48,0,24,0,12,0,6,0,3,0,1,128,0,192,0,96,0,48,0,6,0,0,192,0,24,0,3,0,0,96,0,12,0,1,128,0,48,0,6,0,0,192,0,24,0,3,0,0,96,0,12,0,3,128,0,48,0,24,0,12,0,6,0,3,0,1,128,0,192,0,96,0,48,0,8,0,2,0,0,128,0,32,0,8,0,2,0,0,128,0,32,0,8,0,2,0 };
void display_ECG_animation() {
//    display_frame(ECG_frame);
}

unsigned char free_style_frame[135];
void read_free_style_frame() {
    // expected format of incoming serial data when this function has been called: "123,0,15,...,65,7,0,"

    Serial.setTimeout(12);
    
    for( int i = 0; i < 135; ++i ) {
        free_style_frame[i] = Serial.parseInt();
        Serial.read(); //discard the comma
    }

    Serial.setTimeout(70);
}


//returns true if 'q' was passed on serial monitor and otherwise false
bool parse_serial_data_and_do_stuff() {
    // p<float>: Adjust time Period of rotation in milliseconds e.g. p100.1 will set the period of rotation to 100.1 ms.
    // c:        Start Calibration mode: The display needs to be told what its period of rotation is. 
    // f1:       display 'frame_no1'
    // f2:       display 'frame_no2'
    // f3:       display 'frame_no3'
    // f4:       display 'frame_no4'
    // f5:       display 'frame_no5'
    // a1:       display 'animation_no1'
    // m:        display music visualizer
    // e:        display ECG animation
    // s:        use before sending a free-style frame
    // q:        exit displaying all of the above commands except p<float>
    
    if( Serial.available() > 0 ) {
        char  input_type  = Serial.read();
        float input_value = Serial.parseFloat();
        
        if( input_type == 'p' ) {
            current_time_period = (uint32_t)(input_value * 1000);
        } 
        else if( input_type == 'c' ) {
            while( true ) {
                display_calibration_frame();
                
                bool should_exit = parse_serial_data_and_do_stuff();
                if( should_exit ) {
                    all_led_off();
                    break;
                }
            }
        } 
        else if( input_type == 'f' ) {
            int frame_number = (int)(input_value + 0.5); // proper way to cast a float into an int

            switch( frame_number ) {
                case 1:
                    while( true ) {
                        display_frame( frame_no1 );
                        
                        bool should_exit = parse_serial_data_and_do_stuff();
                        if( should_exit ) {
                            all_led_off();
                            break;
                        }
                    }
                    break;
                case 2:
                    while( true ) {
                        display_frame( frame_no2 );
                        
                        bool should_exit = parse_serial_data_and_do_stuff();
                        if( should_exit ) {
                            all_led_off();
                            break;
                        }
                    }
                    break;
                case 3:
                    while( true ) {
                        display_frame( frame_no3 );
                        
                        bool should_exit = parse_serial_data_and_do_stuff();
                        if( should_exit ) {
                            all_led_off();
                            break;
                        }
                    }
                    break;
                case 4:
                    while( true ) {
                        display_frame( frame_no4 );
                        
                        bool should_exit = parse_serial_data_and_do_stuff();
                        if( should_exit ) {
                            all_led_off();
                            break;
                        }
                    }
                    break;
                case 5:
                    while( true ) {
                        display_frame( frame_no5 );
                        
                        bool should_exit = parse_serial_data_and_do_stuff();
                        if( should_exit ) {
                            all_led_off();
                            break;
                        }
                    }
                    break;
//                case 6:
//                    while( true ) {
//                        display_frame( frame_no6 );
//                        
//                        bool should_exit = parse_serial_data_and_do_stuff();
//                        if( should_exit ) {
//                            all_led_off();  
//                            break;
//                        }
//                    }
//                    break;
//                case 7:
//                    while( true ) {
//                        display_frame( frame_no7 );
//                        
//                        bool should_exit = parse_serial_data_and_do_stuff();
//                        if( should_exit ) {
//                            all_led_off();
//                            break;
//                        }
//                    }
//                    break;
            }
        }
        else if( input_type == 'a' ) {
            int animation_number = (int)(input_value + 0.5); // proper way to cast a float into an int

            switch( animation_number ) {
                case 1:
                    while( true ) {
                        // dinosaur animation
                        display_dino_animation();
                        
                        bool should_exit = parse_serial_data_and_do_stuff();
                        if( should_exit ) {
                            all_led_off();
                            break;
                        }
                    }
                    break;
            }
        }
        else if( input_type == 'm' ) {
            while( true ) {
                display_music_visualizer();
                
                bool should_exit = parse_serial_data_and_do_stuff();
                if( should_exit ) {
                    all_led_off();
                    break;
                }
            }
        }
        else if( input_type == 'e' ) {
            while( true ) {
                display_ECG_animation();
                
                bool should_exit = parse_serial_data_and_do_stuff();
                if( should_exit ) {
                    all_led_off();
                    break;
                }
            }
        }
        else if( input_type == 's' ) {
            delay(100);
            read_free_style_frame();
            while( true ) {
                display_frame(free_style_frame);
                
                bool should_exit = parse_serial_data_and_do_stuff();
                if( should_exit ) {
                    all_led_off();
                    break;
                }
            }
        }
        else if( input_type == 'q' ) {
            return true;
        } 
        else {
            Serial.println("Unrecognized command");
        }
    }

    return false;
}


void setup() {
    Serial.begin(115200);
    Serial.setTimeout(70);
  
    for ( int i = 0; i < 18; ++i ) {
        pinMode(LED_PIN[i], OUTPUT);
        digitalWrite(LED_PIN[i], LOW);
    }

    for ( int i = 0; i < 3; ++i ) { Serial.println("Testing Serial.println()"); }
}

void loop() {
    parse_serial_data_and_do_stuff();
}
