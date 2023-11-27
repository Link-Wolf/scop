/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xxxxxxx <xxxxxxx@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 15:09:00 by xxxxxxx           #+#    #+#             */
/*   Updated: 2023/11/27 13:51:37 by xxxxxxx          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

class Parser;

#ifndef PARSER_CLASS_HPP
# define PARSER_CLASS_HPP
# include "../../includes/scop.hpp"
# include "Scop.class.hpp"

# include <algorithm>

using namespace std;

class Parser
{															
	private:
		unsigned int			_check = 1;
		Scop					&_scop;

	public:
		Parser(Scop &scop, string filename);
		~Parser();

		Scop	&getScop(void);
		
		void	parse(string filename);
		bool	check(void);
};

#endif