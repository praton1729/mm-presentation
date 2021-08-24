struct page {
	unsigned long flags;
	union {
		struct {	/* Page cache and anonymous pages */
			struct list_head lru;
			struct address_space *mapping;
			pgoff_t index;		/* Our offset within mapping. */
			unsigned long private;
		};
		struct {	/* page_pool used by netstack */
			unsigned long pp_magic;
			struct page_pool *pp;
			unsigned long _pp_mapping_pad;
			unsigned long dma_addr[2];
		};
		struct {	/* slab, slob and slub */
			union {
				struct list_head slab_list;
				struct {	/* Partial pages */
					struct page *next;
					int pages;	/* Nr of pages left */
					int pobjects;	/* Approximate count */
				};
			};
			struct kmem_cache *slab_cache; /* not slob */
			void *freelist;		/* first free object */
			union {
				void *s_mem;	/* slab: first object */
				unsigned long counters;		/* SLUB */
				struct {			/* SLUB */
					unsigned inuse:16;
					unsigned objects:15;
					unsigned frozen:1;
				};
			};
		};
		struct {	/* Tail pages of compound page */
			unsigned long compound_head;	/* Bit zero is set */

			/* First tail page only */
			unsigned char compound_dtor;
			unsigned char compound_order;
			atomic_t compound_mapcount;
			unsigned int compound_nr; /* 1 << compound_order */
		};
		struct {	/* Second tail page of compound page */
			unsigned long _compound_pad_1;	/* compound_head */
			atomic_t hpage_pinned_refcount;
			/* For both global and memcg */
			struct list_head deferred_list;
		};
		struct {	/* Page table pages */
			unsigned long _pt_pad_1;	/* compound_head */
			pgtable_t pmd_huge_pte; /* protected by page->ptl */
			unsigned long _pt_pad_2;	/* mapping */
			union {
				struct mm_struct *pt_mm; /* x86 pgds only */
				atomic_t pt_frag_refcount; /* powerpc */
			};
			spinlock_t *ptl;
		};
		struct {	/* ZONE_DEVICE pages */
			struct dev_pagemap *pgmap;
			void *zone_device_data;
		};

		struct rcu_head rcu_head;
	};

	union {		/* This union is 4 bytes in size. */
		atomic_t _mapcount;
		unsigned int page_type;
		unsigned int active;		/* SLAB */
		int units;			/* SLOB */
	};

	atomic_t _refcount;
	unsigned long memcg_data;
	int _last_cpupid;
} _struct_page_alignment;
