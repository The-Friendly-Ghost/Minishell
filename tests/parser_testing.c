/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_testing.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpost <cpost@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/17 14:20:14 by cpost         #+#    #+#                 */
/*   Updated: 2022/08/18 13:41:02 by cpost         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// // main to test if the determine token function is working
// int	main(void)
// {
// 	printf("%d\n", determine_token_type("'hallo dit is een test'"));
// 	printf("%d\n", determine_token_type("\"hallo\""));
// 	printf("%d\n", determine_token_type("\"'\"hallo dit is een test\"'\""));
// 	printf("%d\n", determine_token_type("hallo"));
// 	printf("%d\n", determine_token_type("<"));
// 	printf("%d\n", determine_token_type(">"));
// 	printf("%d\n", determine_token_type("<<"));
// 	printf("%d\n", determine_token_type(">>"));
// 	printf("%d\n", determine_token_type("|"));
// 	printf("%d\n", determine_token_type("$ENV"));
// 	printf("%d\n", determine_token_type("$"));
// 	printf("%d\n", determine_token_type("$?"));
// 	printf("%d\n", determine_token_type("echo"));
// 	printf("%d\n", determine_token_type("cd"));
// 	printf("%d\n", determine_token_type("pwd"));
// 	printf("%d\n", determine_token_type("export"));
// 	printf("%d\n", determine_token_type("unset"));
// 	printf("%d\n", determine_token_type("env"));
// 	printf("%d\n", determine_token_type("exit"));
// 	printf("%d\n", determine_token_type("test"));
// 	printf("%d\n", determine_token_type("'dit is een test'"));
// 	printf("%d\n", determine_token_type("test123"));
// }