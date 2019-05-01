/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_calculations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 14:44:52 by dvoroshy          #+#    #+#             */
/*   Updated: 2018/10/18 14:44:53 by dvoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	round_1(t_md5 *md5)
{
	FF(md5->a, md5->b, md5->c, md5->d, md5->x[0], S11, 0xd76aa478);
	FF(md5->d, md5->a, md5->b, md5->c, md5->x[1], S12, 0xe8c7b756);
	FF(md5->c, md5->d, md5->a, md5->b, md5->x[2], S13, 0x242070db);
	FF(md5->b, md5->c, md5->d, md5->a, md5->x[3], S14, 0xc1bdceee);
	FF(md5->a, md5->b, md5->c, md5->d, md5->x[4], S11, 0xf57c0faf);
	FF(md5->d, md5->a, md5->b, md5->c, md5->x[5], S12, 0x4787c62a);
	FF(md5->c, md5->d, md5->a, md5->b, md5->x[6], S13, 0xa8304613);
	FF(md5->b, md5->c, md5->d, md5->a, md5->x[7], S14, 0xfd469501);
	FF(md5->a, md5->b, md5->c, md5->d, md5->x[8], S11, 0x698098d8);
	FF(md5->d, md5->a, md5->b, md5->c, md5->x[9], S12, 0x8b44f7af);
	FF(md5->c, md5->d, md5->a, md5->b, md5->x[10], S13, 0xffff5bb1);
	FF(md5->b, md5->c, md5->d, md5->a, md5->x[11], S14, 0x895cd7be);
	FF(md5->a, md5->b, md5->c, md5->d, md5->x[12], S11, 0x6b901122);
	FF(md5->d, md5->a, md5->b, md5->c, md5->x[13], S12, 0xfd987193);
	FF(md5->c, md5->d, md5->a, md5->b, md5->x[14], S13, 0xa679438e);
	FF(md5->b, md5->c, md5->d, md5->a, md5->x[15], S14, 0x49b40821);
}

void	round_2(t_md5 *md5)
{
	GG(md5->a, md5->b, md5->c, md5->d, md5->x[1], S21, 0xf61e2562);
	GG(md5->d, md5->a, md5->b, md5->c, md5->x[6], S22, 0xc040b340);
	GG(md5->c, md5->d, md5->a, md5->b, md5->x[11], S23, 0x265e5a51);
	GG(md5->b, md5->c, md5->d, md5->a, md5->x[0], S24, 0xe9b6c7aa);
	GG(md5->a, md5->b, md5->c, md5->d, md5->x[5], S21, 0xd62f105d);
	GG(md5->d, md5->a, md5->b, md5->c, md5->x[10], S22, 0x2441453);
	GG(md5->c, md5->d, md5->a, md5->b, md5->x[15], S23, 0xd8a1e681);
	GG(md5->b, md5->c, md5->d, md5->a, md5->x[4], S24, 0xe7d3fbc8);
	GG(md5->a, md5->b, md5->c, md5->d, md5->x[9], S21, 0x21e1cde6);
	GG(md5->d, md5->a, md5->b, md5->c, md5->x[14], S22, 0xc33707d6);
	GG(md5->c, md5->d, md5->a, md5->b, md5->x[3], S23, 0xf4d50d87);
	GG(md5->b, md5->c, md5->d, md5->a, md5->x[8], S24, 0x455a14ed);
	GG(md5->a, md5->b, md5->c, md5->d, md5->x[13], S21, 0xa9e3e905);
	GG(md5->d, md5->a, md5->b, md5->c, md5->x[2], S22, 0xfcefa3f8);
	GG(md5->c, md5->d, md5->a, md5->b, md5->x[7], S23, 0x676f02d9);
	GG(md5->b, md5->c, md5->d, md5->a, md5->x[12], S24, 0x8d2a4c8a);
}

void	round_3(t_md5 *md5)
{
	HH(md5->a, md5->b, md5->c, md5->d, md5->x[5], S31, 0xfffa3942);
	HH(md5->d, md5->a, md5->b, md5->c, md5->x[8], S32, 0x8771f681);
	HH(md5->c, md5->d, md5->a, md5->b, md5->x[11], S33, 0x6d9d6122);
	HH(md5->b, md5->c, md5->d, md5->a, md5->x[14], S34, 0xfde5380c);
	HH(md5->a, md5->b, md5->c, md5->d, md5->x[1], S31, 0xa4beea44);
	HH(md5->d, md5->a, md5->b, md5->c, md5->x[4], S32, 0x4bdecfa9);
	HH(md5->c, md5->d, md5->a, md5->b, md5->x[7], S33, 0xf6bb4b60);
	HH(md5->b, md5->c, md5->d, md5->a, md5->x[10], S34, 0xbebfbc70);
	HH(md5->a, md5->b, md5->c, md5->d, md5->x[13], S31, 0x289b7ec6);
	HH(md5->d, md5->a, md5->b, md5->c, md5->x[0], S32, 0xeaa127fa);
	HH(md5->c, md5->d, md5->a, md5->b, md5->x[3], S33, 0xd4ef3085);
	HH(md5->b, md5->c, md5->d, md5->a, md5->x[6], S34, 0x4881d05);
	HH(md5->a, md5->b, md5->c, md5->d, md5->x[9], S31, 0xd9d4d039);
	HH(md5->d, md5->a, md5->b, md5->c, md5->x[12], S32, 0xe6db99e5);
	HH(md5->c, md5->d, md5->a, md5->b, md5->x[15], S33, 0x1fa27cf8);
	HH(md5->b, md5->c, md5->d, md5->a, md5->x[2], S34, 0xc4ac5665);
}

void	round_4(t_md5 *md5)
{
	II(md5->a, md5->b, md5->c, md5->d, md5->x[0], S41, 0xf4292244);
	II(md5->d, md5->a, md5->b, md5->c, md5->x[7], S42, 0x432aff97);
	II(md5->c, md5->d, md5->a, md5->b, md5->x[14], S43, 0xab9423a7);
	II(md5->b, md5->c, md5->d, md5->a, md5->x[5], S44, 0xfc93a039);
	II(md5->a, md5->b, md5->c, md5->d, md5->x[12], S41, 0x655b59c3);
	II(md5->d, md5->a, md5->b, md5->c, md5->x[3], S42, 0x8f0ccc92);
	II(md5->c, md5->d, md5->a, md5->b, md5->x[10], S43, 0xffeff47d);
	II(md5->b, md5->c, md5->d, md5->a, md5->x[1], S44, 0x85845dd1);
	II(md5->a, md5->b, md5->c, md5->d, md5->x[8], S41, 0x6fa87e4f);
	II(md5->d, md5->a, md5->b, md5->c, md5->x[15], S42, 0xfe2ce6e0);
	II(md5->c, md5->d, md5->a, md5->b, md5->x[6], S43, 0xa3014314);
	II(md5->b, md5->c, md5->d, md5->a, md5->x[13], S44, 0x4e0811a1);
	II(md5->a, md5->b, md5->c, md5->d, md5->x[4], S41, 0xf7537e82);
	II(md5->d, md5->a, md5->b, md5->c, md5->x[11], S42, 0xbd3af235);
	II(md5->c, md5->d, md5->a, md5->b, md5->x[2], S43, 0x2ad7d2bb);
	II(md5->b, md5->c, md5->d, md5->a, md5->x[9], S44, 0xeb86d391);
}

void	md5_transform(t_md5 *md5, unsigned char block[64])
{
	md5->a = md5->state[0];
	md5->b = md5->state[1];
	md5->c = md5->state[2];
	md5->d = md5->state[3];
	chars_to_words(md5->x, block, 64);
	round_1(md5);
	round_2(md5);
	round_3(md5);
	round_4(md5);
	md5->state[0] += md5->a;
	md5->state[1] += md5->b;
	md5->state[2] += md5->c;
	md5->state[3] += md5->d;
}
