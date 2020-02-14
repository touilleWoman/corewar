# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    script_test.sh                                     :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nabih <naali@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/01 07:20:49 by nabih             #+#    #+#              #
#    Updated: 2020/02/11 17:36:51 by nabih            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

./asm $1.s
hexdump $1.cor > mon_resultat.txt
./asm_zaz $1.s
hexdump $1.cor > zaz_resultat.txt
diff -u mon_resultat.txt zaz_resultat.txt
rm mon_resultat.txt zaz_resultat.txt
