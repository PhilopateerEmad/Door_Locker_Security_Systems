 /******************************************************************************
 * MODULE: COMMON MACROS
 * File Name: common_macros.h
 * Description: common used macros
 * Created on: Sep 30, 2021
 * Author: Philo
 *******************************************************************************/

#ifndef COMMON_MACROS_H_
#define COMMON_MACROS_H_

/* set bit in a given register*/
#define SET_BIT(REG,BIT_NUM) (REG |= (1<<BIT_NUM))

/*clear bit in a given register */
#define CLEAR_BIT(REG,BIT_NUM) (REG &=~(1<<BIT_NUM))

/* toggle bit in a given register */
#define TOGGLE_BIT(REG,BIT_NUM) (REG ^=(1<<BIT_NUM))

/*rotate right the register by specific transitions*/
#define ROR(REG,NUM) (REG = (REG>>NUM)|(REG<<(8-NUM)))

/*rotate left the register by specific transitions*/
#define ROL(REG,NUM) (REG = (REG<<NUM)|(REG>>(8-NUM)))

/*check if a bit is set returns 0 or 1 this is a condition not event */
#define BIT_IS_SET(REG,BIT_NUM) (REG&(1<<BIT_NUM))

/*check if a bit is cleared returns 0 or 1 this is a condition not event*/
#define BIT_IS_CLEAR(REG,BIT_NUM)  (!(REG&(1<<BIT_NUM)))

#endif /* COMMON_MACROS_H_ */
