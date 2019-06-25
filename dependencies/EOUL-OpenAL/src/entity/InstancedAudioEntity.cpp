#include <EOUL-OpenAL\entity\InstancedAudioEntity.h>

namespace EOUL {

	namespace OpenAL {

		InstancedAudioEntity::InstancedAudioEntity(const InstancedBuffer& buffer) : Audio(buffer.buffer, true), buffer(buffer) {

		}

	}

}