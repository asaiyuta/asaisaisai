#pragma once 
#include <Array>

union Packet12bit{
	uint8_t buffer[2];
	uint16_t data;
};

template <std::size_t size> 
class RoughlyProtcol12bit{
public:
	RoughlyProtcol12bit(){
		for(auto& e : packet){
			e.data = 0;
		}
	}
	~RoughlyProtcol12bit(){
	}
	
	inline Packet12bit& operator [](std::size_t index){
		return packet[index];
	}

	inline uint8_t header() const{
		return makeHeader();
	}
	
	inline uint8_t checkSum() const{
		return makeCheckSum();
	}
	
	inline bool isCheck(const uint8_t checkSum) const{
		return (checkSum == makeCheckSum())	;
	}
	
	inline uint8_t readPacketLength(uint8_t header) const{
		if(header > 0b10000000) return (header - 0b10000000);
		return 0;
	}
	
	inline uint8_t writePacketLength() const {
		return (packet.size() * 2);
	}
	
	inline void encord(){
		this -> packetsEncord();
	}
	inline void decord(){
		this -> packetsDecord();
	}

private:
	inline uint8_t makeHeader() const{
		return (uint8_t)(0b10000000 + (packet.size() * 2));
	}
	
	inline uint8_t makeCheckSum() const{
		uint64_t sum(0);
		for(auto& e : packet){
			sum += e.buffer[0];
			sum += e.buffer[1];
		}
		sum /= (packet.size() * 2);
		return sum;
	}
	
	inline void packetsEncord(){
		for(auto& e : packet){
			uint16_t EncData = e.data;
			e.buffer[0] = (EncData & 0b00111111) << 1;
			e.buffer[1] = (EncData & 0b0000111111000000) >> 5;
		}
	}
	
	inline void packetsDecord(){
		for(auto& e : packet){
			uint16_t DecData = e.buffer[1] << 5;
			DecData += e.buffer[0] >> 1;
			e.data = DecData;
		}
	}
	
	std::array<Packet12bit,size> packet;
};

