#ifndef NODE_H_
#define NODE_H_

#define NODE(i) (((uint8_t*)&node)[i])
#define CLEAR_NODE()                                                           \
    {                                                                          \
        for (int ii = 0; ii < 8; ++ii) NODE(ii) = 0;                           \
    }

/**
 * A variable that stores serial data input from UART.
 *
 * NODE(i)         accesses i-th field as a l-value. 0 <= i < 8.
 * CLEAR_NODE()    resets every field.
 *
 * @note 패딩 문제로 union 부분이 NODE(4)가 되는 현상 있음.
 * 속도 향상을 위해 패딩 비활성화 대신 미사용 변수 padding[2]를 사용할 수 있음.
 * 이 경우 NODE(4-9)로 데이터 부분을 사용하게 됨.
 */
typedef struct __attribute__((__packed__)) Node {
    unsigned char class;      // NODE(0)
    unsigned char data_size;  // NODE(1)
    union {
        struct {
            unsigned char r1 : 2;  // reserved
            unsigned char FS : 2;
            unsigned char r2 : 1;  // reserved
            unsigned char DC : 2;
            unsigned char ES : 1;
        };
        unsigned char data[6];  // NODE(2-7)
    };
} NODE;

extern NODE node;

#define GET_CLASS() ((NODE(0)) - ('0'))

enum CLASS {
    CLASS_CONTROL = '0',
    CLASS_UPDATE = '1'
};

enum FS {
    FS_FIRST = 1,
    FS_SECOND,
    FS_THIRD
};

enum DC {
    DC_CLOSE = 1,
    DC_OPEN
};

#endif /* NODE_H_ */
