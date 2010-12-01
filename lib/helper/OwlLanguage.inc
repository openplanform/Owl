<?php

/* vim: set syn=php expandtab tabstop=4 shiftwidth=4 softtabstop=4: */

/**																			 
 *  ,_,  
 * (o,o) 
 * {`"'}   OWL (Open Web Library)
 * -"-"-
 * 
 * Software distribuido bajo la "GNU GENERAL PUBLIC LICENSE v3", 
 * mas información en /doc/LICENSE
 * 
 * <Descripción de la clase>
 * 
 * @category Owl
 * @package Owl
 * @license GNU GPL V3 (http://www.gnu.org/licenses/gpl-3.0.txt)
 * @author Nicolás Daniel Palumbo <npalumbo@xinax.net> 
 * @author Aaron Amengual Arranz <aaron.amengual@gmail.com> 
 * @version 0.5.4
 * @since 0.3
 * 
 */

class OwlLanguage{
	
	/**
	 * Iso con el idioma actual
	 * @var string
	 */
	protected $lang = 'es';
	
	/**
	 * Array con los meses en castellano
	 * @var array
	 */
	protected $mesesEs = array("Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio", "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre");

	/**
	 * Array con los meses en catalán
	 * @var array
	 */
	protected $mesesCt = array("Gener", "Febrer", "Març", "Abril", "Maig", "Juny", "Juliol", "Agost", "Setembre", "Octubre", "Novembre", "Decembre");
	
	/**
	 * Array con los meses en inglés
	 * @var array
	 */
	protected $mesesEn = array("January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December");
	
	/**
	 * Array con los paises en castellano ES
	 * @var array
	 */
	protected $paisesEs = array(
		 "es" => "España",
		 "uk" => "Reino Unido",
		 "de" => "Alemania",
		 "fr" => "Francia",
		 "af" => "Afganistán",
		 "al" => "Albania",
		 "ad" => "Andorra",
		 "ao" => "Angola",
		 "ai" => "Anguila",
		 "ag" => "Antigua y Barbuda",
		 "an" => "Antillas Holandesas",
		 "aq" => "Antártica",
		 "sa" => "Arabia Saudita",
		 "dz" => "Argelia",
		 "ar" => "Argentina",
		 "am" => "Armenia",
		 "aw" => "Aruba",
		 "au" => "Australia",
		 "at" => "Austria",
		 "az" => "Azerbaidjan",
		 "bs" => "Bahamas",
		 "bh" => "Bahrain",
		 "bd" => "Bangladesh",
		 "bb" => "Barbados",
		 "bz" => "Belice",
		 "bj" => "Benin",
		 "bm" => "Bermuda",
		 "bt" => "Bhutan",
		 "by" => "Bielorusia",
		 "bo" => "Bolivia",
		 "ba" => "Bosnia-Herzegovina",
		 "bw" => "Botswana",
		 "br" => "Brasil",
		 "bn" => "Brunei Darussalam",
		 "bg" => "Bulgaria",
		 "bf" => "Burkina Faso",
		 "bi" => "Burundi",
		 "be" => "Bélgica",
		 "cv" => "Cabe Verde",
		 "kh" => "Camboya",
		 "cm" => "Camerún",
		 "ca" => "Canadá",
		 "ky" => "Cayman Islands",
		 "td" => "Chad",
		 "cl" => "Chile",
		 "cn" => "China",
		 "cy" => "Chipre",
		 "co" => "Colombia",
		 "km" => "Comoras",
		 "cg" => "Congo",
		 "kp" => "Corea del norte",
		 "kr" => "Corea del sur",
		 "ci" => "Costa Marfil",
		 "cr" => "Costa Rica",
		 "hr" => "Croacia",
		 "cu" => "Cuba",
		 "dk" => "Dinamarca",
		 "dj" => "Djibouti",
		 "dm" => "Dominica",
		 "ec" => "Ecuador",
		 "eg" => "Egypto",
		 "sv" => "El Salvador",
		 "ae" => "Emiratos Árabes Unidos",
		 "er" => "Eritrea",
		 "si" => "Eslovenia",
		 "us" => "Estados Unidos",
		 "ee" => "Estonia",
		 "et" => "Etiopía",
		 "fk" => "Falkland Islands (Islas Malvinas)",
		 "fj" => "Fiji",
		 "ph" => "Filipinas",
		 "fi" => "Finlandia",
		 "ga" => "Gabón",
		 "gm" => "Gambia",
		 "ge" => "Georgia",
		 "gh" => "Ghana",
		 "gd" => "Granada",
		 "gr" => "Grecia",
		 "gl" => "Groenlandia",
		 "gp" => "Guadelupe (Francesa)",
		 "gu" => "Guam (USA)",
		 "gt" => "Guatemala",
		 "gg" => "Guernsey",
		 "gn" => "Guinea",
		 "gw" => "Guinea Bissau",
		 "gq" => "Guinea Ecuatorial",
		 "gy" => "Guyana",
		 "gf" => "Guyana Francesa",
		 "ht" => "Haití",
		 "nl" => "Holanda",
		 "hn" => "Honduras",
		 "hk" => "Hong Kong",
		 "hu" => "Hungría",
		 "in" => "India",
		 "id" => "Indonesia",
		 "iq" => "Iraq",
		 "ie" => "Irlanda",
		 "ir" => "Irán",
		 "bv" => "Isla Bouvet",
		 "cc" => "Isla Cocos (Keeling Islands)",
		 "im" => "Isla de Man",
		 "is" => "Islandia",
		 "cx" => "Islas Christmas",
		 "ck" => "Islas Cook",
		 "fo" => "Islas Faroe",
		 "hm" => "Islas Heard y McDonald",
		 "mh" => "Islas Marshall",
		 "pn" => "Islas Pitcairn",
		 "gs" => "Islas S. Georgia y S. Sandwich",
		 "sb" => "Islas Salomón",
		 "sj" => "Islas Svalbard y Jan Mayen",
		 "tc" => "Islas Turcos y Caicos",
		 "vg" => "Islas Vírgenes (Reino Unido)",
		 "vi" => "Islas Vírgenes (USA)",
		 "wf" => "Islas Wallis y Futuna",
		 "il" => "Israel",
		 "it" => "Italia",
		 "jm" => "Jamaica",
		 "jp" => "Japón",
		 "je" => "Jersey",
		 "jo" => "Jordania",
		 "kz" => "Kazakhstan",
		 "ke" => "Kenya",
		 "ki" => "Kiribati",
		 "kw" => "Kuwait",
		 "kg" => "Kyrgyzstan",
		 "la" => "Laos",
		 "ls" => "Lesotho",
		 "lv" => "Letonia",
		 "lr" => "Liberia",
		 "ly" => "Libia",
		 "li" => "Liechtenstein",
		 "lt" => "Lituania",
		 "lu" => "Luxemburgo",
		 "lb" => "Líbano",
		 "mo" => "Macao",
		 "mk" => "Macedonia",
		 "mg" => "Madagascar",
		 "my" => "Malasia",
		 "mw" => "Malawi",
		 "mv" => "Maldivas",
		 "ml" => "Mali",
		 "mt" => "Malta",
		 "ma" => "Marruecos",
		 "mq" => "Martinica (Francesa)",
		 "mu" => "Mauricia",
		 "mr" => "Mauritania",
		 "yt" => "Mayotte",
		 "fm" => "Micronesia",
		 "md" => "Moldavia",
		 "mn" => "Mongolia",
		 "me" => "Montenegro",
		 "ms" => "Montserrat",
		 "mz" => "Mozambique",
		 "mm" => "Myanmar",
		 "mx" => "México",
		 "mc" => "Mónaco",
		 "na" => "Namibia",
		 "nr" => "Nauru",
		 "np" => "Nepal",
		 "ni" => "Nicaragua",
		 "ne" => "Niger",
		 "ng" => "Nigeria",
		 "nu" => "Niue",
		 "nf" => "Norfolk Island",
		 "mp" => "Northern Mariana Islands",
		 "no" => "Noruega",
		 "nc" => "Nueva Caledonia (Francesa)",
		 "nz" => "Nueva Zelanda",
		 "om" => "Omán",
		 "pk" => "Pakistán",
		 "pw" => "Palau",
		 "pa" => "Panamá",
		 "pg" => "Papua Nueva Guinea",
		 "py" => "Paraguay",
		 "pe" => "Perú",
		 "pf" => "Polinesia (Francesa)",
		 "pl" => "Polonia",
		 "pt" => "Portugal",
		 "pr" => "Puerto Rico",
		 "qa" => "Qatar",
		 "cf" => "República Central Africana",
		 "cz" => "República Checa",
		 "cs" => "República Checa y Eslovakia",
		 "cd" => "República Democratica del Congo",
		 "do" => "República Dominicana",
		 "sk" => "República Eslovaca",
		 "re" => "Reunión (Francesa)",
		 "ro" => "Rumanía",
		 "ru" => "Rusia",
		 "rw" => "Rwanda",
		 "pm" => "Saint Pierre y Miquelon",
		 "ws" => "Samoa",
		 "as" => "Samoa Americana",
		 "kn" => "San Cristóbal y Nieves",
		 "sm" => "San Marino",
		 "vc" => "San Vicente y Granadinas",
		 "sh" => "Santa Helena",
		 "lc" => "Santa Lucía",
		 "st" => "Sao Tomé y Príncipe",
		 "sn" => "Senegal",
		 "rs" => "Serbia",
		 "sc" => "Seychelles",
		 "sl" => "Sierra Leona",
		 "sg" => "Singapore",
		 "sy" => "Siria",
		 "so" => "Somalia",
		 "lk" => "Sri Lanka",
		 "sd" => "Sudán",
		 "se" => "Suecia",
		 "ch" => "Suiza",
		 "sr" => "Suriname",
		 "sz" => "Swaziland",
		 "eh" => "Sáhara Occidental",
		 "tj" => "Tadjikistán",
		 "th" => "Tailandia",
		 "tw" => "Taiwán",
		 "tz" => "Tanzania",
		 "io" => "Territorio Británico del Oceano Índico",
		 "tf" => "Territorios Franceses de Sur",
		 "tp" => "Timor del Este",
		 "tg" => "Togo",
		 "tk" => "Tokelau",
		 "to" => "Tonga",
		 "tt" => "Trinidad y Tobago",
		 "tm" => "Turkmenia",
		 "tr" => "Turquía",
		 "tv" => "Tuvalu",
		 "tn" => "Túnez",
		 "um" => "USA Isla Menores",
		 "ua" => "Ucrania",
		 "ug" => "Uganda",
		 "uy" => "Uruguay",
		 "uz" => "Uzbekistán",
		 "vu" => "Vanuatu",
		 "va" => "Vaticano",
		 "ve" => "Venezuela",
		 "vn" => "Vietnam",
		 "ye" => "Yemen",
		 "zr" => "Zaire",
		 "zm" => "Zambia",
		 "zw" => "Zimbabwe",
		 "za" => "África del Sur",	
	);
	
	/**
	 * Array con los países en catalán (CT)
	 * @var array
	 */
	protected $paisesCt = array(
		 "es" => "Espanya",
		 "uk" => "Regne Unit",
		 "de" => "Alemanya",
		 "fr" => "França",
		 "af" => "Afganistan",
		 "al" => "Albània",
		 "dz" => "Algèria",
		 "ad" => "Andorra",
		 "ao" => "Angola",
		 "ai" => "Anguilla",
		 "ag" => "Antigua i Barbuda",
		 "an" => "Antilles Holandeses",
		 "aq" => "Antàrtida",
		 "ar" => "Argentina",
		 "am" => "Armènia",
		 "aw" => "Aruba",
		 "sa" => "Aràbia Saudita",
		 "au" => "Austràlia",
		 "az" => "Azerbaian",
		 "bs" => "Bahamws",
		 "bh" => "Bahrain",
		 "bd" => "Bangladesh",
		 "bb" => "Barbados",
		 "bz" => "Belize",
		 "bj" => "Benin",
		 "bm" => "Bermuda",
		 "bt" => "Bhutan",
		 "by" => "Bielorrússia",
		 "bo" => "Bolívia",
		 "bw" => "Botswana",
		 "br" => "Brasil",
		 "bn" => "Brunei",
		 "bg" => "Bulgària",
		 "bf" => "Burkina Faso",
		 "bi" => "Burundi",
		 "be" => "Bèlgica",
		 "ba" => "Bòsnia i Hercegovina",
		 "kh" => "Cambodja",
		 "cm" => "Camerun",
		 "ca" => "Canadà",
		 "cv" => "Cap Verd",
		 "va" => "Ciutat del Vaticà",
		 "co" => "Colòmbia",
		 "km" => "Comores",
		 "cg" => "Congo",
		 "kp" => "Corea del Nord",
		 "kr" => "Corea del Sud",
		 "cr" => "Costa Rica",
		 "ci" => "Costa d'Ivori",
		 "hr" => "Croàcia",
		 "cu" => "Cuba",
		 "dk" => "Dinamarca",
		 "dj" => "Djibouti",
		 "dm" => "Dominica",
		 "us" => "EUA",
		 "eg" => "Egipte",
		 "sv" => "El Salvador",
		 "ae" => "Emirats Àrabs Units",
		 "ec" => "Equador",
		 "er" => "Eritrea",
		 "sk" => "Eslovàquia",
		 "si" => "Eslovènia",
		 "ee" => "Estònia",
		 "et" => "Etiòpia",
		 "fj" => "Fiji",
		 "ph" => "Filipines",
		 "fi" => "Finlàndia",
		 "ga" => "Gabó",
		 "ge" => "Georgia",
		 "gh" => "Ghana",
		 "gd" => "Grenada",
		 "gl" => "Groenlàndia",
		 "gr" => "Grècia",
		 "gp" => "Guadalupe",
		 "gy" => "Guaiana",
		 "gf" => "Guaiana Francesa",
		 "gu" => "Guam",
		 "gt" => "Guatemala",
		 "gg" => "Guernsey",
		 "gn" => "Guinea",
		 "gw" => "Guinea Bissau",
		 "gq" => "Guinea Equatorial",
		 "gm" => "Gàmbia",
		 "ht" => "Haití",
		 "hn" => "Hondures",
		 "hk" => "Hong Kong",
		 "hu" => "Hongria",
		 "ye" => "Iemen",
		 "bv" => "Illa Bouvet",
		 "cx" => "Illa Christmas",
		 "cc" => "Illa Coco",
		 "gs" => "Illa Geòrgies del Sud i Illes Sandwich Australs",
		 "yt" => "Illa Mayotte",
		 "nu" => "Illa Nive",
		 "nf" => "Illa Norfolk",
		 "re" => "Illa Réunion",
		 "ky" => "Illes Caiman",
		 "ck" => "Illes Cook",
		 "fo" => "Illes Fer-Oer",
		 "hm" => "Illes Heard i Macdonald",
		 "mv" => "Illes Maldives",
		 "fk" => "Illes Malvines",
		 "mp" => "Illes Marianes",
		 "mh" => "Illes Marshall",
		 "pn" => "Illes Pitcairn",
		 "sb" => "Illes Salomó",
		 "sc" => "Illes Seychelles",
		 "tk" => "Illes Tokelau",
		 "tc" => "Illes Turques i Caicos",
		 "vg" => "Illes Virgin (Regne Unit)",
		 "vi" => "Illes Virgin (USA)",
		 "um" => "Illes menors allunyades dels Estats Units",
		 "id" => "Indonèsia",
		 "ir" => "Iran",
		 "iq" => "Iraq",
		 "ie" => "Irlanda",
		 "im" => "Isla de Man",
		 "is" => "Islàndia",
		 "il" => "Israel",
		 "it" => "Itàlia",
		 "jm" => "Jamaica",
		 "jp" => "Japó",
		 "je" => "Jersey",
		 "jo" => "Jordània",
		 "kz" => "Kazakhstan",
		 "ke" => "Kenya",
		 "kg" => "Kirguizistan",
		 "ki" => "Kiribati",
		 "kw" => "Kuwait",
		 "la" => "Laos",
		 "ls" => "Lesotho",
		 "lv" => "Letònia",
		 "lr" => "Libèria",
		 "li" => "Liechtenstein",
		 "lt" => "Lituània",
		 "lu" => "Luxemburg",
		 "lb" => "Líban",
		 "ly" => "Líbia",
		 "mo" => "Macao",
		 "mk" => "Macedònia",
		 "mg" => "Madagascar",
		 "my" => "Malaisia",
		 "mw" => "Malawi",
		 "ml" => "Mali",
		 "mt" => "Malta",
		 "ma" => "Marroc",
		 "mq" => "Martinica",
		 "mu" => "Maurici",
		 "mr" => "Mauritània",
		 "fm" => "Micronèsia",
		 "md" => "Moldàvia",
		 "mn" => "Mongòlia",
		 "me" => "Montenegro",
		 "ms" => "Montserrat",
		 "mz" => "Moçambic",
		 "mm" => "Myanmar",
		 "mx" => "Mèxic",
		 "mc" => "Mònaco",
		 "na" => "Namíbia",
		 "nr" => "Nauru",
		 "np" => "Nepal",
		 "ni" => "Nicaragua",
		 "ng" => "Nigèria",
		 "no" => "Noruega",
		 "nc" => "Nova Caledònia",
		 "nz" => "Nova Zelanda",
		 "ne" => "Níger",
		 "om" => "Oman",
		 "pk" => "Pakistan",
		 "pw" => "Palaos",
		 "pa" => "Panamà",
		 "pg" => "Papua-Nova Guinea",
		 "py" => "Paraguai",
		 "nl" => "Països Baixos",
		 "pe" => "Perú",
		 "pf" => "Polinèsia francesa",
		 "pl" => "Polònia",
		 "pt" => "Portugal",
		 "pr" => "Puerto Rico",
		 "qa" => "Qatar",
		 "cs" => "Republica Checa y Eslovakia",
		 "cf" => "República Centroafricana",
		 "cd" => "República Democràtica del Congo",
		 "do" => "República Dominicana",
		 "cz" => "República Xeca",
		 "ro" => "Romania",
		 "rw" => "Rwanda",
		 "ru" => "Rússia",
		 "kn" => "Saint Christopher i Nevis",
		 "pm" => "Saint Pierre et Miquelon",
		 "vc" => "Saint Vicent and Grenadines",
		 "ws" => "Samoa",
		 "as" => "Samoa Americana",
		 "sm" => "San Marino",
		 "sh" => "Santa Elena",
		 "lc" => "Santa Lucía",
		 "sn" => "Senegal",
		 "sl" => "Sierra Leone",
		 "sg" => "Singapur",
		 "so" => "Somàlia",
		 "lk" => "Sri Lanka",
		 "sd" => "Sudan",
		 "za" => "Sudàfrica",
		 "sr" => "Surinam",
		 "se" => "Suècia",
		 "ch" => "Suïssa",
		 "sj" => "Svalbard i Jan Mayen",
		 "sz" => "Swazilàndia",
		 "eh" => "Sàhara Occidental",
		 "st" => "São Tomé i Príncipe",
		 "rs" => "Sèrbia",
		 "sy" => "Síria",
		 "tj" => "Tadjikistan",
		 "th" => "Tailàndia",
		 "tw" => "Taiwan",
		 "tz" => "Tanzània",
		 "io" => "Territori Britànic de l'Oceà Índic",
		 "tf" => "Territoris australs francesos",
		 "tp" => "Timor ",
		 "tg" => "Togo",
		 "to" => "Tonga",
		 "tt" => "Trinitat i Tobago",
		 "tn" => "Tuníssia",
		 "tm" => "Turkmeninstan",
		 "tr" => "Turquia",
		 "tv" => "Tuvalu",
		 "td" => "Txad",
		 "ua" => "Ucraïna",
		 "ug" => "Uganda",
		 "uy" => "Uruguai",
		 "uz" => "Uzbekistan",
		 "vu" => "Vanuatu",
		 "ve" => "Veneçuela",
		 "vn" => "Vietnam",
		 "wf" => "Wallis i Futuna",
		 "cl" => "Xile",
		 "cn" => "Xina",
		 "cy" => "Xipre",
		 "zr" => "Zaire",
		 "zw" => "Zimbawe",
		 "zm" => "Zàmbia",
		 "at" => "Àustria",
		 "in" => "Índia",
	);
	
	/**
	 * Array con los países en inglés (EN)
	 * @var array
	 */	
	protected $paisesEn = array(
		 "es" => "Spain",
		 "uk" => "United Kingdom",
		 "de" => "Germany",
		 "fr" => "France",
		 "af" => "Afghanistan",
		 "al" => "Albania",
		 "dz" => "Algeria",
		 "as" => "American Samoa",
		 "ad" => "Andorra, Principality of",
		 "ao" => "Angola",
		 "ai" => "Anguilla",
		 "aq" => "Antartica",
		 "ag" => "Antigua and Barbuda",
		 "ar" => "Argentina",
		 "am" => "Armenia",
		 "aw" => "Aruba",
		 "au" => "Australia",
		 "at" => "Austria",
		 "az" => "Azerbaidjan",
		 "bs" => "Bahamas",
		 "bh" => "Bahrain",
		 "bd" => "Bangladesh",
		 "bb" => "Barbados",
		 "by" => "Belarus",
		 "be" => "Belgium",
		 "bz" => "Belize",
		 "bj" => "Benin",
		 "bm" => "Bermuda",
		 "bt" => "Bhutan",
		 "bo" => "Bolivia",
		 "ba" => "Bosnia-Herzegovina",
		 "bw" => "Botswana",
		 "bv" => "Bouvet Island",
		 "br" => "Brazil",
		 "io" => "British Indian Ocean Territory",
		 "bn" => "Brunei Darussalam",
		 "bg" => "Bulgaria",
		 "bf" => "Burkina Faso",
		 "bi" => "Burundi",
		 "kh" => "Cambodia, Kingdom of",
		 "cm" => "Cameroon",
		 "ca" => "Canada",
		 "cv" => "Cape Verde",
		 "ky" => "Cayman Islands",
		 "cf" => "Central African Republic",
		 "td" => "Chad",
		 "cl" => "Chile",
		 "cn" => "China",
		 "cx" => "Christmas Island",
		 "cc" => "Cocos (Keeling) Islands",
		 "co" => "Colombia",
		 "km" => "Comoros",
		 "cg" => "Congo",
		 "cd" => "Congo, The Democratic Republic of the",
		 "ck" => "Cook Islands",
		 "cr" => "Costa Rica",
		 "hr" => "Croatia",
		 "cu" => "Cuba",
		 "cy" => "Cyprus",
		 "cz" => "Czech Republic",
		 "dk" => "Denmark",
		 "dj" => "Djibouti",
		 "dm" => "Dominica",
		 "do" => "Dominican Republic",
		 "tp" => "East Timor",
		 "ec" => "Ecuador",
		 "eg" => "Egypt",
		 "sv" => "El Salvador",
		 "gq" => "Equatorial Guinea",
		 "er" => "Eritrea",
		 "ee" => "Estonia",
		 "et" => "Ethiopia",
		 "fk" => "Falkland Islands (Malvinas)",
		 "fo" => "Faroe Islands",
		 "fj" => "Fiji",
		 "fi" => "Finland",
		 "cs" => "Former Czechoslovakia",
		 "gf" => "French Guyana",
		 "tf" => "French Southern Territories",
		 "ga" => "Gabon",
		 "gm" => "Gambia",
		 "ge" => "Georgia",
		 "gh" => "Ghana",
		 "gr" => "Greece",
		 "gl" => "Greenland",
		 "gd" => "Grenada",
		 "gp" => "Guadeloupe (French)",
		 "gu" => "Guam (USA)",
		 "gt" => "Guatemala",
		 "gg" => "Guernsey, C.I.",
		 "gn" => "Guinea",
		 "gw" => "Guinea-Bissau",
		 "gy" => "Guyana",
		 "ht" => "Haiti",
		 "hm" => "Heard and McDonald Islands",
		 "va" => "Holy See (Vatican City State)",
		 "hn" => "Honduras",
		 "hk" => "Hong Kong",
		 "hu" => "Hungary",
		 "is" => "Iceland",
		 "in" => "India",
		 "id" => "Indonesia",
		 "ir" => "Iran (Islamic Republic of)",
		 "iq" => "Iraq",
		 "ie" => "Ireland",
		 "im" => "Isle of Man",
		 "il" => "Israel",
		 "it" => "Italy",
		 "ci" => "Ivory Coast (Cote D'Ivoire)",
		 "jm" => "Jamaica",
		 "jp" => "Japan",
		 "je" => "Jersey, C.I.",
		 "jo" => "Jordan",
		 "kz" => "Kazakhstan",
		 "ke" => "Kenya",
		 "ki" => "Kiribati",
		 "kp" => "Korea, Dem. People's Rep of",
		 "kr" => "Korea, Republic of",
		 "kw" => "Kuwait",
		 "kg" => "Kyrgyz Republic (Kyrgyzstan)",
		 "la" => "Lao Peoples Democratic Republic",
		 "lv" => "Latvia",
		 "lb" => "Lebanon",
		 "ls" => "Lesotho",
		 "lr" => "Liberia",
		 "ly" => "Libyan Arab Jamahiriya",
		 "li" => "Liechtenstein",
		 "lt" => "Lithuania",
		 "lu" => "Luxembourg",
		 "mo" => "Macau",
		 "mk" => "Macedonia, The Former Yugoslav",
		 "mg" => "Madagascar",
		 "mw" => "Malawi",
		 "my" => "Malaysia",
		 "mv" => "Maldives",
		 "ml" => "Mali",
		 "mt" => "Malta",
		 "mh" => "Marshall Islands",
		 "mq" => "Martinique (French)",
		 "mr" => "Mauritania",
		 "mu" => "Mauritius",
		 "yt" => "Mayotte",
		 "mx" => "Mexico",
		 "fm" => "Micronesia, Fed. States of",
		 "md" => "Moldova, Republic of",
		 "mc" => "Monaco",
		 "mn" => "Mongolia",
		 "me" => "Montenegro",
		 "ms" => "Montserrat",
		 "ma" => "Morocco",
		 "mz" => "Mozambique",
		 "mm" => "Myanmar",
		 "na" => "Namibia",
		 "nr" => "Nauru",
		 "np" => "Nepal",
		 "nl" => "Netherlands",
		 "an" => "Netherlands Antilles",
		 "nc" => "New Caledonia (French)",
		 "nz" => "New Zealand",
		 "ni" => "Nicaragua",
		 "ne" => "Niger",
		 "ng" => "Nigeria",
		 "nu" => "Niue",
		 "nf" => "Norfolk Island",
		 "mp" => "Northern Mariana Islands",
		 "no" => "Norway",
		 "om" => "Oman",
		 "pk" => "Pakistan",
		 "pw" => "Palau",
		 "pa" => "Panama",
		 "pg" => "Papua New Guinea",
		 "py" => "Paraguay",
		 "pe" => "Peru",
		 "ph" => "Philippines",
		 "pn" => "Pitcairn Island",
		 "pl" => "Poland",
		 "pf" => "Polynesia (French)",
		 "pt" => "Portugal",
		 "pr" => "Puerto Rico",
		 "qa" => "Qatar",
		 "re" => "Reunion (French)",
		 "ro" => "Romania",
		 "ru" => "Russian Federation",
		 "rw" => "Rwanda",
		 "gs" => "S. Georgia and S. Sandwich Isls.",
		 "sh" => "Saint Helena",
		 "kn" => "Saint Kitts and Nevis Anguilla",
		 "lc" => "Saint Lucia",
		 "pm" => "Saint Pierre and Miquelon",
		 "st" => "Saint Tome (Sao Tome) and Principe",
		 "vc" => "Saint Vincent and Grenadines",
		 "ws" => "Samoa",
		 "sm" => "San Marino",
		 "sa" => "Saudi Arabia",
		 "sn" => "Senegal",
		 "rs" => "Serbia",
		 "sc" => "Seychelles",
		 "sl" => "Sierra Leone",
		 "sg" => "Singapore",
		 "sk" => "Slovak Republic",
		 "si" => "Slovenia",
		 "sb" => "Solomon Islands",
		 "so" => "Somalia",
		 "za" => "South Africa",
		 "lk" => "Sri Lanka",
		 "sd" => "Sudan",
		 "sr" => "Suriname",
		 "sj" => "Svalbard and Jan Mayen Islands",
		 "sz" => "Swaziland",
		 "se" => "Sweden",
		 "ch" => "Switzerland",
		 "sy" => "Syrian Arab Republic",
		 "tj" => "Tadjikistan",
		 "tw" => "Taiwan",
		 "tz" => "Tanzania, United Republic of",
		 "th" => "Thailand",
		 "tg" => "Togo",
		 "tk" => "Tokelau",
		 "to" => "Tonga",
		 "tt" => "Trinidad and Tobago",
		 "tn" => "Tunisia",
		 "tr" => "Turkey",
		 "tm" => "Turkmenistan",
		 "tc" => "Turks and Caicos Islands",
		 "tv" => "Tuvalu",
		 "um" => "USA Minor Outlying Islands",
		 "ug" => "Uganda",
		 "ua" => "Ukraine",
		 "ae" => "United Arab Emirates (U.A.E.)",
		 "us" => "United States",
		 "uy" => "Uruguay",
		 "uz" => "Uzbekistan",
		 "vu" => "Vanuatu",
		 "ve" => "Venezuela",
		 "vn" => "Vietnam",
		 "vg" => "Virgin Islands (British)",
		 "vi" => "Virgin Islands (USA)",
		 "wf" => "Wallis and Futuna Islands",
		 "eh" => "Western Sahara",
		 "ye" => "Yemen, Republic of",
		 "zr" => "Zaire",
		 "zm" => "Zambia",
		 "zw" => "Zimbabwe"	
	);
	
	/**
	 * Establece el idioma actual
	 * @param string $lang
	 * @return void
	 */
	public function __construct( $lang = 'es'){
		
		$this->lang = $lang;
		
	}

	/**
	 * Devuelve un array con los paises indexados
	 * por su código iso (2 letras) en el idioma actual
	 * @return array
	 */
	public function getPaisesMultilang(){
		
		if (method_exists($this, 'getPais' . ucfirst($this->lang))){
			return call_user_func(array($this, 'getPais' . ucfirst($this->lang)));
		} 
		
	}
	
	/**
	 * Devuelve un array con los paises indexados
	 * por su código iso (2 letras) en castellano
	 * @return array
	 */
	public function getPaisesEs(){
		
		return $this->paisesEs;             
		
	}
	
	/**
	 * Devuelve un array con los paises indexados
	 * por su código iso (2 letras) en catalán
	 * @return array
	 */
	public function getPaisesCt(){

		return $this->paisesCt;
		
	}
	
	
	/**
	 * Devuelve un array con los paises indexados
	 * por su código iso (2 letras) en inglés
	 * @return array
	 */
	public function getPaisesEn(){

		return $this->paisesEn;
		
	}
	
	/**
	 * Imprime el codigo html para generar un
	 * combo selector de paises
	 * @return void
	 */
	public function echoComboPaisesEs($selected = null){
		
		?><select name="pais" id="pais">
            <option value=""></option>
            <?
            
            foreach($this->paisesEs as $isoPais=>$nombrePais){
            	
            	$selectedStr = '';
            	if (!is_null($selected) && $isoPais == $selected){
            		$selectedStr = ' selected="selected" ';
            	}
            	
            	echo '<option value="'.$isoPais.'"' . $selectedStr . '>'.$nombrePais.'</option>' . "\n";
            		
            }
            
        ?></select><?
		
	}
	
	/**
	 * Imprime el codigo html para generar un
	 * combo selector de paises
	 * @return void
	 */
	public function echoComboPaisesCt(){
		
		?><select name="pais" id="pais">
            <option value=""></option>
            <?
            
            foreach($this->paisesCt as $isoPais=>$nombrePais){
            	
            	echo '<option value="'.$isoPais.'">'.$nombrePais.'</option>' . "\n";
            		
            }
            
        ?></select><?
		
	}	
	
	/**
	 * Imprime el codigo html para generar un
	 * combo selector de paises
	 * @return void
	 */
	public function echoComboPaisesEn(){
		
		?><select name="pais" id="pais">
            <option value=""></option>
            <?
            
            foreach($this->paisesEn as $isoPais=>$nombrePais){
            	
            	echo '<option value="'.$isoPais.'">'.$nombrePais.'</option>' . "\n";
            		
            }
            
        ?></select><?
		
	}	
	
	/**
	 * Devuelve un pais en castellano a partir de su codigo iso
	 * @param string $iso
	 * @return string
	 */
	public function getPaisEs($iso){
		
		if (array_key_exists($iso, $this->paisesEs)){
			return $this->paisesEs[$iso];
		}
		
	}
	
	/**
	 * Devuelve un array con los meses en el idioma actual
	 * @return array
	 */
	public function getMesesMultilang(){

		if (method_exists($this, 'getMeses' . ucfirst($this->lang)) ){

			return call_user_func(array($this,'getMeses' . ucfirst($this->lang)));
			
		}
		
	}
	
	/**
	 * Devuelve un array con los meses en castellano
	 * @return array
	 */
	public function getMesesEs(){
		
		return $this->mesesEs;
		
	}
	
	/**
	 * Devuelve un array con los meses en catalán
	 * @return array
	 */
	public function getMesesCt(){
		
		return $this->mesesCt;
		
	}
	
	/**
	 * Devuelve un array con los meses en inglés
	 * @return array
	 */
	public function getMesesEn(){
		
		return $this->mesesEn;
		
	}
	
}

?>