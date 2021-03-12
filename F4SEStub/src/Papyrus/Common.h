#pragma once

#define BIND(a_method, ...) a_vm.BindNativeMethod(obj, #a_method##sv, a_method __VA_OPT__(, ) __VA_ARGS__)

namespace Papyrus
{
	using RE::BSScript::structure_wrapper;
	using Severity = RE::BSScript::ErrorLogger::Severity;

	inline auto GetReferenceData(const RE::GameScript::RefrOrInventoryObj& a_data)
		-> std::optional<std::pair<RE::TESBoundObject*, RE::BSTSmartPointer<RE::ExtraDataList>>>
	{
		if (a_data.Reference()) {
			const auto ref = a_data.Reference();
			return std::make_pair(ref->GetObjectReference(), ref->extraList);
		} else if (a_data.Container() && a_data.UniqueID()) {
			const auto cont = a_data.Container();
			const auto uniqueID = a_data.UniqueID();
			if (const auto inv = cont->inventoryList; inv) {
				const RE::BSAutoReadLock l{ inv->rwLock };
				for (const auto& item : inv->data) {
					for (auto stack = item.stackData.get(); stack; stack = stack->nextStack.get()) {
						const auto xID =
							stack->extra ?
                                stack->extra->GetByType<RE::ExtraUniqueID>() :
                                nullptr;
						if (xID && xID->uniqueID == uniqueID) {
							return std::make_pair(item.object, stack->extra);
						}
					}
				}
			}
		}

		return std::nullopt;
	}

	namespace detail
	{
		template <class T>
		class BasicDelayFunctor :
			public RE::GameScript::DelayFunctor
		{
		private:
			using super = RE::GameScript::DelayFunctor;

		public:
			using FunctorType = RE::GameScript::DelayFunctor::FunctorType;

			BasicDelayFunctor(std::uint32_t a_stackID, std::function<T()> a_fn) :
				super(a_stackID),
				_fn(std::move(a_fn))
			{}

			[[nodiscard]] RE::BSScript::Variable operator()() override
			{
				RE::BSScript::Variable result;
				RE::BSScript::PackVariable(result, _fn());
				return result;
			}

			[[nodiscard]] bool IsLatent() const override { return false; }
			[[nodiscard]] FunctorType GetType() const override { return static_cast<FunctorType>(-1); }
			bool SaveImpl(RE::BSStorage&) const override { return false; }
			bool LoadImpl(const RE::BSStorage&, std::uint32_t, bool&) override { return false; }

		private:
			std::function<T()> _fn;
		};
	}

	template <class F>
	bool QueuePostRenderCall(std::uint32_t a_stackID, F&& a_fn)
	{
		using result_t = std::invoke_result_t<F&&>;
		static_assert(RE::BSScript::detail::ValidateReturn<result_t>());
		const auto vm = RE::GameVM::GetSingleton();
		return vm &&
		       vm->QueuePostRenderCall(
				   RE::make_smart<detail::BasicDelayFunctor<result_t>>(
					   a_stackID,
					   std::forward<F>(a_fn)));
	}
}
