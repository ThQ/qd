<?php
    class BigInt {
		private $bits = Array();
		private $width = 0;

		function __construct($value,$width=false) {
			if(!isset($value)) {
				return null;
			}

			if($width) {
				$this->FindWidth($width);
			}

			if(is_array($value)) {
				if(count($value) > $this->width) {
					throw new Exception('Array larger than integer width');
				}
				$this->bits = $value;
			} else {
				$this->Parse($value);
			}
		}

		/**
			Add a BigInt to this one and return the result.
			NOTE: 	Be very careful here. The width will never increase to
					compensate for any extra bits. For instance when adding
					0101 (5) and 1011 (13) you would get 10010 (18), this will 
					be transformed to 0011 (3). Because 18 mod 15 (1111) = 3 (0011)
					Another example:
					1000 (8) + 1110 (14) = 10110 (22) => 0111 (7)
		*/
		public function Add(BigInt $int) {
			if($int->Width() != $this->width) {
				throw new Exception("Format error :: BigInts must be of equal size!");
			}

			$carry = 0;
			$count = $this->width;
			$arr = $int->ToBitArray();
			$ret = $this->InitializeArray($count);
		
			for($i = $count-1; $i > -1; $i--) {
				$tmp = $this->bits[$i] + $arr[$i] + $carry;
				if($tmp == 2) {
					$ret[$i] = 0;
					$carry = 1;
				} else if($tmp == 3) {
					$ret[$i] = 1;
					$carry =  1;
				} else {
					$ret[$i] = $tmp;
					$carry = 0;
				}
			}
	
			return $this->ToBigInt($ret);
		}
		
		/**
			Shift this BigInt left by $steps positions.
			The added bits on the right are zeros.
		*/
		public function ArithmeticLeftShift($steps) {
			$count = $this->width;
			$ret = $this->InitializeArray($count);
			for($i = $steps; $i < $count; $i++) {
				$ret[$i-$steps] = $this->bits[$i];
			}
			$off = $count - $steps;
			for($i = $off; $i < $count; $i++) {
				$ret[$i] = 0;
			}
			return $this->ToBigInt($ret);
		}

		/**
			This function is an alias to ArithmeticLeftShift()
		*/
		public function LogicalLeftShift($steps) {
			return $this->ArithmeticLeftShift($steps);
		}

		/**
			Shift this BigInt right by $steps positions.
			This method is only suitable for unsigned BigInts.
		*/
		public function LogicalRightShift($steps) {
			$count = $this->width;
			$ret = $this->InitializeArray($count);
			$off = $count - $steps;
			for($i = 0; $i < $off; $i++) {
				$ret[$i+$steps] = $this->bits[$i];
			}
			return $this->ToBigInt($ret);
		}

		/**
			Shift this BigInt right by $steps positions.
			This method honours the sign-bit on the BigInt.
		*/
		public function ArithmeticRightShift($steps) {
			$count = $this->width;
			$ret = $this->InitializeArray($count);
			$off = $count - $steps;
			for($i = 0; $i < $off; $i++) {
				$ret[$i+$steps] = $this->bits[$i];
			}
			// Preserve sign-bit
			$ret[0] = $this->bits[0];

			return $this->ToBigInt($ret);
		}

		/**
			Rotate this BigInt right by $steps positions.
		*/
		public function RightRotate($steps) {
			$count = $this->width;
			$ret = $this->InitializeArray($count);

			$steps = $steps % $count;

			$off = $count - $steps;
			for($i = 0; $i < $off; $i++) {
				$ret[$i+$steps] = $this->bits[$i];
			}
			for($i = $off; $i < $count; $i++) {
				$ret[$i-$off] = $this->bits[$i];
			}
			
			return $this->ToBigInt($ret);
		}

		/**
			Rotate this BigInt left by $steps positions.
		*/
		public function LeftRotate($steps) {
			$count = $this->width;
			$ret = $this->InitializeArray($count);

			$steps = $steps % $count;

			$off = $count - $steps;
			for($i=0;$i < $steps; $i++) {
				$ret[$i+$off] = $this->bits[$i];
			}
			$j=0;
			for($i=$steps;$i < $count; $i++) {
				$ret[$j++] = $this->bits[$i];
			}
			return $this->ToBigInt($ret);
		}
	
		/**
			Return a new BigInt object containing the result
			of a logical OR operation on this BigInt and $bigint.
		*/
		public function LogicalOR(BigInt $bigint) {
			if($bigint == null) {
				throw new Exception("Argument error :: bigint cannot be null!");
			}

			if($this->width != $bigint->Width()) {
				throw new Exception("Format error :: BigInts must be of equal size!");
			}

			$bigint_arr = $bigint->ToBitArray();
			$ret = $this->InitializeArray($this->width);

			for($i = 0; $i < $this->width; $i++) {
				$ret[$i] = ($this->bits[$i] != $bigint_arr[$i]) || ($this->bits[$i] == 1 && $bigint_arr[$i] == 1) ? 1 : 0;
			}

			return $this->ToBigInt($ret);
		}

		/**
			Return a new BigInt object containing the result
			of a logical XOR operation on this BigInt and $bigint.
		*/
		public function LogicalXOR(BigInt $bigint) {
			if($bigint == null) {
				throw new Exception("Argument error :: bigint cannot be null!");
			}

			$count = $this->width;
			if($count != $bigint->Width()) {
				throw new Exception("Format error :: BigInts must be of equal size!");
			}

			$bigint_arr = $bigint->ToBitArray();
			$ret = $this->InitializeArray($count);

			for($i = 0; $i < $count; $i++) {
				$ret[$i] = ($this->bits[$i] != $bigint_arr[$i]) ? 1 : 0;
			}

			return $this->ToBigInt($ret);
		}

		/**
			Return a new BigInt object containing the result
			of a logical AND operation on this BigInt and $bigint.
		*/
		public function LogicalAND(BigInt $bigint) {
			if($bigint == null) {
				throw new Exception("Argument error :: bigint cannot be null!");
			}

			$count = $this->width;
			if($count != $bigint->Width()) {
				throw new Exception("Format error :: BigInts must be of equal size!");
			}

			$bigint_arr = $bigint->ToBitArray();
			$ret = $this->InitializeArray($count);

			for($i = 0; $i < $count; $i++) {
				if(($this->bits[$i] == 1) && ($bigint_arr[$i]) == 1) {
					$ret[$i] = 1;
				}
			}

			return $this->ToBigInt($ret);
		}

		/**
			Return a new BigInt object containing the result of
			a logical NOT operation on this BigInt.
		*/
		public function LogicalNOT() {
			$ret = $this->InitializeArray($this->width);

			for($i = 0; $i < $this->width; $i++) {
				$ret[$i] = ($this->bits[$i] == 1) ? 0 : 1;
			}

			return $this->ToBigInt($ret);
		}

		/**
			Return the string representation of this BigInt
		*/
		public function ToString($val=null) {
			$ret = "";
			$arr = ($val == null) ? $this->bits : $val;
			for($i=0;$i<(count($arr) - 1);$i++) {
				$ret .= $arr[$i];
			}
			
			$ret = str_pad($ret,$this->width,"0",STR_PAD_LEFT);

			return $ret;
		}

		/**
			This function is an alias of ToString().
			This function will be automagically called by print()
			and echo()
		*/
		public function __toString() {
			return $this->ToString();
		}

		/**
			Return this BigInt as an array of bits.
		*/
		public function ToBitArray() {
			return $this->bits;
		}

		public function ToInt() {
			$ret = 0;
			$pow = 0;
			for($i=$this->width-1;$i>=0;$i--) {
				if($this->bits[$i] == 1) {
					$ret += pow(2,$pow);
				}
				$pow++;
			}
			return $ret;
		}

		public function ToHex() {
			$steps = $this->width / 4;
			$ret = "";
			$bits = array();

			for($i = 0; $i < $steps; $i++) {
				$off = $i * 4;
				for($j = 0; $j < 4; $j++) {
					$bits[$j] = $this->bits[$off+$j];
				}
				$ret .= $this->BitsToHexNumeral($bits);
			}

			return $ret;
		}

		private function BitsToHexNumeral($bits) {
			$ret = 0;
			if(count($bits) > 4) {
				throw new Exception('Format Exception :: Cannot convert a number to hex of larger than 4 bits.');
			}
			$pow = 0;
			for($i = 3; $i > -1; $i--) {
				if($bits[$i] == 1) {
					$ret += pow(2,$pow);
				}
				$pow++;
			}

			return dechex($ret);
		}

		public static function FromBitString($bits,$width=false) {
			$arr = array();

			if($width === false) {
				$width = strlen($bits);
			}
			if($width > strlen($bits)) {
				$bits = str_pad($bits,$width,"0",STR_PAD_LEFT);
			}
			try {
				for($i = 0; $i < $width; $i++) {
					$arr[$i] = substr($bits,$i,1);
				}
			} catch(Exception $ex) {
				echo $ex->getMessage()."\n";
			}

			return new BigInt($arr,$width);
		}
		
		/**
			Return the width of this BigInt.
			The value of Width() is the number of bits that is
			needed to contain the BigInt value.
		*/
		public function Width() {
			return $this->width;
		}

		/** PRIVATES **/

		/**
			Initialize an array of $width bits wide.
		*/
		private function InitializeArray($width) {
			$ret = array();
			for($i=0;$i<$width;$i++) {
				$ret[$i] = 0;
			}
			return $ret;
		}

		/**
			Convert an array of bits to a BigInt object.
		*/
		private function ToBigInt($arr) {
			return new BigInt($arr,$this->width);
		}
		
		/**
			Parse a string value containing an integer and
			create a new BigInt object that contains the binary
			representation of that integer.
		*/
		private function Parse($value) {
			$pow = 0;
			while(($value - pow(2,$pow++)) > 0);

			if($this->width == 0) {
				$this->FindWidth(--$pow);
			}

			if(($pow-1) > $this->width) {
				throw new Exception('Overflow! Expected '.$this->width.' got '.($pow-1));
			} else if($pow != $this->width) {
				$this->bits = $this->InitializeArray($this->width);
				for($i = 0; $i < $this->width; $i++) {
					$this->bits[$i] = 0;
				}
			}

			$off = $this->width - 1;
			for($i = $pow; $i >= 0; $i--) {
				$tmp = $value - pow(2,$i);
				if($tmp >= 0) {
					$this->bits[$off-$i] = 1;
					$value = $tmp;
				} else {
					$this->bits[$off-$i] = 0;
				}
			}
		}

		/**
			Attempt to determine the minimum number of bits
			required to store the integer.
			This function will return at least 8 bits (standard integer)
			and will double the width for every iteration, for example:
			0, 1, 2, 4, 8, 16, 32, etc
		*/
		private function FindWidth($w) {
			$this->width = 0;
			$w_pow = pow(2,$w);
			while(($w_pow - pow(2,$this->width)) > 0) {
				if($this->width == 0) {
					$this->width = 1;
				} else {
					$this->width = $this->width * 2;
				}
			}
		}
	}

	/*
		SHA256 Algorithm
		Copyright (c) 2005 Sander van Vliet and Justin Verweel, All rights reserved
		Date: 19-10-2005
		Current version: 0.1
	*/

	/* vim: set noet ts=4 sw=4 ft=php: :*/


	// The first sixty-four 32 bit word constants.
	// These words represent the first thirty-two bits of
	// the fractional parts of the cube roots of the first
	// sixty-four prime numbers.
	$K = array(	'1116352408','1899447441','3049323471','3921009573','961987163','1508970993','2453635748','2870763221',
			'3624381080','310598401','607225278','1426881987','1925078388','2162078206','2614888103','3248222580',
			'3835390401','4022224774','264347078','604807628','770255983','1249150122','1555081692','1996064986',
			'2554220882','2821834349','2952996808','3210313671','3336571891','3584528711','113926993','338241895',
			'666307205','773529912','1294757372','1396182291','1695183700','1986661051','2177026350','2456956037',
			'2730485921','2820302411','3259730800','3345764771','3516065817','3600352804','4094571909','275423344',
			'430227734','506948616','659060556','883997877','958139571','1322822218','1537002063','1747873779',
			'1955562222','2024104815','2227730452','2361852424','2428436474','2756734187','3204031479','3329325298'
		);

	for($i=0;$i<count($K);$i++) {
		$K[$i] = new BigInt($K[$i]);
	}

	function sha256($str) {
		global $K;

		$M = pad_message($str);

		/*// Initial hash values
		$iA = new BigInt('1779033703');
		$iB = new BigInt('3144134277');
		$iC = new BigInt('1013904242');
		$iD = new BigInt('2773480762');
		$iE = new BigInt('1359893119');
		$iF = new BigInt('2600822924');
		$iG = new BigInt('528734635');
		$iH = new BigInt('1541459225');

		$N = count($M);

		// Needed only once, it will be completely overwritten by each pass
		$Wnew = array();

		for($i = 0; $i < $N; $i++) {
			$iOldA = $iA;
			$iOldB = $iB;
			$iOldC = $iC;
			$iOldD = $iD;
			$iOldE = $iE;
			$iOldF = $iF;
			$iOldG = $iG;
			$iOldH = $iH;

			$W = convert_512_block_to_words($M[$i]);

			for($t = 0; $t < 64; $t++) {
				if($t < 16) {
					$Wnew[$t] = $W[$t];
				} else {
					$Wnew[$t] = sigma1_256($Wnew[$t-2])->Add($Wnew[$t-7])->Add(sigma0_256($Wnew[$t-15]))->Add($Wnew[$t-16]);
				}

				$T1 = $iH->Add(bigSigma1_256($iE))->Add(ch($iE,$iF,$iG))->Add($K[$t])->Add($Wnew[$t]);
				$T2 = bigSigma0_256($iA)->Add(Maj($iA,$iB,$iC));

				$iH = $iG;
				$iG = $iF;
				$iF = $iE;
				$iE = $iD->Add($T1);
				$iD = $iC;
				$iC = $iB;
				$iB = $iA;
				$iA = $T1->Add($T2);
			}

			$iA = $iOldA->Add($iA);
			$iB = $iOldB->Add($iB);
			$iC = $iOldC->Add($iC);
			$iD = $iOldD->Add($iD);
			$iE = $iOldE->Add($iE);
			$iF = $iOldF->Add($iF);
			$iG = $iOldG->Add($iG);
			$iH = $iOldH->Add($iH);
		}
		
		return $iA->ToHex()." ".$iB->ToHex()." ".$iC->ToHex()." ".$iD->ToHex()." ".$iE->ToHex()." ".$iF->ToHex()." ".$iG->ToHex()." ".$iH->ToHex();
        */
	}

	function pad_message($str) {
		$strlen = strlen($str);

		// NOTE: 8 is the size in bits of a byte (single char string)
		$l = $strlen * 8;

		$bitstr = "";

		for($i = 0; $i < $strlen; $i++) {
			$tmp = substr($str,$i,1);
            echo "char [" . $tmp . "] ord [" . ord($tmp) . "] decbin[" . decbin( ord($tmp)) . "]\n";
			$tmp = decbin(ord($tmp));
            
			$tmp = str_pad($tmp,8,0,STR_PAD_LEFT);
			$bitstr .= $tmp;
		}

        
		// Append 1 bit
		$bitstr .= "1";
        echo "bitstring:" . $bitstr . "\n";

        echo "int_pad_len:" . (($l + 1 + 64) % 512) . "\n";
		$padlen = 512 - (($l + 1 + 64) % 512);
        echo "pad_len:" . $padlen . "\n";
		$padding = str_pad($padding,$padlen,0);
		$bitstr .= $padding;
		
		// Calculate 64 bit length
		$tmp = new BigInt($l);
		$bitstr .= str_pad($tmp->ToString(),64,"0",STR_PAD_LEFT);

		$blocks = strlen($bitstr) / 512;

		$ret = Array();
		for($i = 0; $i < $blocks; $i++) {
			$ret[$i] = substr($bitstr,$i*512,512);
		}

		return $ret;
	}

	function convert_512_block_to_words($block) {
		$ret = array();

		for($i = 0; $i < 16; $i++) {
			$tmp = substr($block,$i*32,32);
			$ret[$i] = BigInt::FromBitString($tmp,32);
		}

		return $ret;
	}

	function ch($x, $y, $z) {
		$t1 = $y->LogicalXOR($z);
		$t2 = $x->LogicalAND($t1);
		$t3 = $z->LogicalXOR($t2);

		return $t3;
	}

	function maj($x, $y, $z) {
		return $x->LogicalAND($y)->LogicalOR($z->LogicalAND($x->LogicalOR($y)));
	}

	function bigSigma0_256($x) {
		$t1 = $x->RightRotate(2);
		$t2 = $x->RightRotate(13);
		$t3 = $x->RightRotate(22);

		return $t1->LogicalXOR($t2)->LogicalXOR($t3);
	}

	function bigSigma1_256($x) {
		$t1 = $x->RightRotate(6);
		$t2 = $x->RightRotate(11);
		$t3 = $x->RightRotate(25);

		return $t1->LogicalXOR($t2)->LogicalXOR($t3);
	}

	function sigma0_256($x){
		$t1 = $x->RightRotate(7);
		$t2 = $x->RightRotate(18);
		$t3 = $x->LogicalRightShift(3);
		
		return $t1->LogicalXOR($t2)->LogicalXOR($t3);
	}
	
	function sigma1_256($x){
		$t1 = $x->RightRotate(17);
		$t2 = $x->RightRotate(19);
		$t3 = $x->LogicalRightShift(10);
		
		return $t1->LogicalXOR($t2)->LogicalXOR($t3);
	}

    echo sha256("lazy_one");
?>

