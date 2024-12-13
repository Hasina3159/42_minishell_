/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazafin <arazafin@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 11:17:19 by arazafin          #+#    #+#             */
/*   Updated: 2024/10/11 19:55:51 by arazafin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

# define ERROR 1
# define SUCCESS 0
# define CMD_MAX 4092
# define TOKENS_MAX 2048
# define T_COMMAND -1
# define T_WORD 0
# define T_STRING_S 1
# define T_STRING_D 18
# define T_OPERATOR 2
# define T_PIPE 3
# define T_IN 4
# define T_OUT 5
# define T_AND 6
# define T_OR 7
# define T_OUT_APPEND 8
# define T_HERE_DOC 9
# define T_P_OPEN 10
# define T_P_CLOSE 11
# define T_VAR 12
# define T_HD 13
# define T_FILE_IN 14
# define T_FILE_OUT 15
# define T_END 16
# define T_HD_ENDER 17
# define FILE_DIR 0
# define FILE_FILE 42
# define FILE_ALL 2048
# define CMD_NOT_FOUND 127
# define T_SPACE 128
# define HISTORY ".history"
# define SH "VeryBadBash> "

#endif
