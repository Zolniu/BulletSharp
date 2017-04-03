#pragma once

namespace BulletSharp
{
	ref class ManifoldPoint;
	ref class CollisionObject;
#ifdef BT_USE_EFFICIENT_CONTACT_PROCESSED
	value struct ManifoldPointCompact;
#endif

#ifdef BT_CALLBACKS_ARE_EVENTS
	public delegate void ContactDestroyedEventHandler(Object^ userPersistantData);
	public delegate void ContactProcessedEventHandler(ManifoldPoint^ cp, CollisionObject^ body0, CollisionObject^ body1);
#ifdef BT_USE_EFFICIENT_CONTACT_PROCESSED
	public delegate void EfficientContactProcessedEventHandler(ManifoldPointCompact cp, int body0UserIndex, int body2UserIndex);
#endif
#else
	public delegate bool ContactDestroyed(Object^ userPersistantData);
	public delegate bool ContactProcessed(ManifoldPoint^ cp, CollisionObject^ body0, CollisionObject^ body1);
#endif

	public value struct PersistentManifold
	{
	internal:
		btPersistentManifold* _native;

		PersistentManifold(btPersistentManifold* native);

#ifdef BT_CALLBACKS_ARE_EVENTS
		static ContactDestroyedEventHandler^ _contactDestroyed;
		static ContactProcessedEventHandler^ _contactProcessed;
#ifdef BT_USE_EFFICIENT_CONTACT_PROCESSED
		static EfficientContactProcessedEventHandler^ _efficientContactProcessed;
#endif

	public:
		static event ContactDestroyedEventHandler^ ContactDestroyed
		{
			void add(ContactDestroyedEventHandler^ callback);
			void remove(ContactDestroyedEventHandler^ callback);
		}
		static event ContactProcessedEventHandler^ ContactProcessed
		{
			void add(ContactProcessedEventHandler^ callback);
			void remove(ContactProcessedEventHandler^ callback);
		}

#ifdef BT_USE_EFFICIENT_CONTACT_PROCESSED
		static event EfficientContactProcessedEventHandler^ EfficientContactProcessed
		{
			void add(EfficientContactProcessedEventHandler^ callback);
			void remove(EfficientContactProcessedEventHandler^ callback);
		}
#endif
#else
		static ContactDestroyed^ _contactDestroyed;
		static ContactProcessed^ _contactProcessed;

	public:
		static property ContactDestroyed^ ContactDestroyed
		{
			::ContactDestroyed^ get();
			void set(::ContactDestroyed^ value);
		}

		static property ContactProcessed^ ContactProcessed
		{
			::ContactProcessed^ get();
			void set(::ContactProcessed^ value);
		}
#endif
/*
		PersistentManifold();
		PersistentManifold(CollisionObject^ body0, CollisionObject^ body1, int __unnamed2,
			btScalar contactBreakingThreshold, btScalar contactProcessingThreshold);
*/
		int AddManifoldPoint(ManifoldPoint^ newPoint, bool isPredictive);
		int AddManifoldPoint(ManifoldPoint^ newPoint);
		void ClearManifold();
		void ClearUserCache(ManifoldPoint^ pt);
		virtual bool Equals(Object^ obj) override;
		int GetCacheEntry(ManifoldPoint^ newPoint);
		virtual int GetHashCode() override;
		ManifoldPoint^ GetContactPoint(int index);
		void RefreshContactPoints(Matrix trA, Matrix trB);
		void RemoveContactPoint(int index);
		void ReplaceContactPoint(ManifoldPoint^ newPoint, int insertIndex);
		void SetBodies(CollisionObject^ body0, CollisionObject^ body1);
		bool ValidContactDistance(ManifoldPoint^ pt);
		static bool operator== (PersistentManifold value1, PersistentManifold value2);
		static bool operator!= (PersistentManifold value1, PersistentManifold value2);

		property CollisionObject^ Body0
		{
			CollisionObject^ get();
		}

		property CollisionObject^ Body1
		{
			CollisionObject^ get();
		}

		property int CompanionIDA
		{
			int get();
			void set(int value);
		}

		property int CompanionIDB
		{
			int get();
			void set(int value);
		}

		property btScalar ContactBreakingThreshold
		{
			btScalar get();
			void set(btScalar contactBreakingThreshold);
		}

		property btScalar ContactProcessingThreshold
		{
			btScalar get();
			void set(btScalar contactProcessingThreshold);
		}

		property int Index1A
		{
			int get();
			void set(int value);
		}

		property int NumContacts
		{
			int get();
			void set(int cachedPoints);
		}

		static PersistentManifold Zero;
	};
};
