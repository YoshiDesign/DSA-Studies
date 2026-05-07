<?php

class Vertex {

    // `readonly` - php 8.1+
    // public readonly string $id;
    private static int $counter = 0;
    protected ?int $x = null, $y = null;

    function __construct(
        public readonly string $id, 
        int $x, 
        int $y) 
    {
        // $this->id = (string) $x . (string) $y . "-" . (string) self::$counter++;
        $this->x = $x;
        $this->y = $y;

    }

    public function position() {
        return array($this->x, $this->y);
    }

}

class DSU {

    // Array of Vertices
    private array $parent = [];

    function __construct(array $vertices) {
        foreach ($vertices as $v) {
            if (!$v instanceof Vertex) {
                throw new InvalidArgumentException("All items must be a <Vertex>");
            }
        }
        echo "Creating Union Finder with " . count($vertices) . " Vertices\n";
    }

    // Create a tree with root $v 
    public function make_set(Vertex $v): void {
        $this->parent[$v->id] = $v;
    }

    /**
     * Combine 2 sets
     * 1. Find the root of $a
     * 2. Find the root of $b
     * 3. If they have the same root, they're already in the same set. Do nothing
     * 4. Otherwise, specify one of the roots as being the root of the other.
     */
    public function union_sets(Vertex $a, Vertex $b): void {
        $root_a = $this->find_set($a);
        $root_b = $this->find_set($b);

        if ($root_a->id != $root_b->id) {
            $this->parent[$root_b->id] = $root_a;
        }

    }

    public function find_set(Vertex $v): int {

        if ($v->id == $parent[$v->id]->id) {
            return $v;
        }

        return $this->parent[$v->id] = $this->find_set($parent[$v->id]);
    }

}

function main() {

    $vertices = [];
    for($i = 0; $i < 100; $i++) {
        $vert = new Vertex(
            'vertex-' . (string) $i, // id
            random_int(1,30), // x
            random_int(1,30)  // y
        );
        printf("New Vertex: %s\n", $vert->id);
        $vertices[$vert->id] = $vert;
    }

    $union = new DSU($vertices);

    echo "Creating sets... ";
    foreach($vertices as $v) {
        $union->make_set($v);
    }
    echo "Done!\n\n";



}

main();