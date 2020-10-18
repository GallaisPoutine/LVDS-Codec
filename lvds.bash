
function bitmap_create {
	for i in {0..7}; do
		bitmap[$i]="R$i"
		bitmap[8+$i]="G$i"
		bitmap[16+$i]="B$i"
	done

	bitmap[18]="HS"
	bitmap[19]="VS"
	bitmap[20]="DE"
	bitmap[21]="CE"
	bitmap[22]="CI"
	bitmap[23]="TOOGLE"
	bitmap[24]="1"
	bitmap[25]="0"

	readonly -p -a bitmap;
}

function filter_value {
	local tmpreg=${1^^}

	if [[ "$tmpreg" == 0X* ]]; then
		tmpreg=${tmpreg:2}
	fi
	echo $tmpreg
}

function hex2bin {
	local pad=$(printf '%0.1s' "0"{1..32})
	local tmpreg=$(filter_value $1)

	local binreg=`echo "obase=2; ibase=16; $tmpreg" | bc`

	if [[ ${#binreg} < 32 ]]; then
		local tmppad=$(printf '%*.*s' 0 $((32 - ${#binreg})) "$pad")
		binreg="$tmppad$binreg"
	fi

	echo $binreg
}

function parse_reg {
	for i in $(seq 0 5 15); do
		map[$i]=${1:12+$i:5}
		echo $i ${map[@]}
	done
}

function main {
	if [ "$#" -ne 3 ]; then
		echo "Bad arguments"
		exit 1
	fi

	bitmap_create
	msb=$(hex2bin $1)
	lsb=$(hex2bin $2)
	parse_reg $msb
	for bit in ${map[@]}; do
		echo -n ${bitmap[`echo "$((2#$bit))"`]}
	done
}

declare -a bitmap;
declare -a map

main $1
